#include <3ds.h>
#include <citro3d.h>
#include <string.h>
#include "cps2.h"
#include "display.h"

enum { LCD_W = 400, LCD_H = 240, TV_W = 320, TEX_W = 512, TEX_H = 256 };
enum { FRAME_PIXELS = CPS2_WIDTH * CPS2_HEIGHT,
       FRAME_BYTES = FRAME_PIXELS * sizeof(uint16_t), INPUT_SLOTS = 3 };
#define RGB565_TRANSFER (GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGB565) | \
                         GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB565))
extern const u32 astra_quad_shader[], astra_quad_shader_end[];

static bool native, gpu_ready, c3d_ready, frame_open;
static uint16_t *inputs, *writable;
static const uint16_t *in_flight, *ready, *last_picture;
static uint32_t submitted;
static uint16_t fallback[CPS2_WIDTH * CPS2_HEIGHT];
static uint16_t source_x[LCD_W], source_y[LCD_H];
static unsigned width, height, clear_buffers;
static void *padded;
static C3D_Tex texture;
static C3D_RenderTarget *target;
static DVLB_s *shader;
static shaderProgram_s program;

static enum cabinet_view cabinet;
uint32_t display_directions(uint32_t buttons, enum cabinet_view view)
{
    if (view != VIEW_DPAD_TOP && view != VIEW_DPAD_BOTTOM) return buttons;
    uint32_t out = buttons & ~(CPS2_UP | CPS2_DOWN | CPS2_LEFT | CPS2_RIGHT);
    bool top = view == VIEW_DPAD_TOP;
    if (buttons & CPS2_UP) out |= top ? CPS2_RIGHT : CPS2_LEFT;
    if (buttons & CPS2_DOWN) out |= top ? CPS2_LEFT : CPS2_RIGHT;
    if (buttons & CPS2_LEFT) out |= top ? CPS2_UP : CPS2_DOWN;
    if (buttons & CPS2_RIGHT) out |= top ? CPS2_DOWN : CPS2_UP;
    return out;
}

void display_set_view(bool use_native, enum cabinet_view view)
{
    native = use_native;
    cabinet = view;
    width = view == VIEW_PORTRAIT ? 180 : view != VIEW_HORIZONTAL ? LCD_W : native ? CPS2_WIDTH : TV_W;
    height = view != VIEW_HORIZONTAL ? LCD_H : native ? CPS2_HEIGHT : LCD_H;
    unsigned horizontal = view == VIEW_PORTRAIT ? CPS2_HEIGHT : CPS2_WIDTH;
    unsigned vertical = view == VIEW_PORTRAIT ? CPS2_WIDTH : CPS2_HEIGHT;
    for (unsigned x = 0; x < width; ++x) source_x[x] = (2*x+1)*horizontal/(2*width);
    for (unsigned y = 0; y < height; ++y) source_y[y] = (2*y+1)*vertical/(2*height);
    clear_buffers = 2;
}

static void release_gpu(void)
{
    if (frame_open) C3D_FrameEnd(GX_CMDLIST_FLUSH);
    // Fini waits for outstanding transfers, then destroys its render targets.
    if (c3d_ready) C3D_Fini();
    if (program.vertexShader) shaderProgramFree(&program);
    if (shader) DVLB_Free(shader);
    if (texture.data) C3D_TexDelete(&texture);
    if (padded) vramFree(padded);
    if (inputs) linearFree(inputs);
    c3d_ready = gpu_ready = frame_open = false;
    inputs = padded = NULL;
    writable = NULL;
    in_flight = ready = last_picture = NULL;
    texture.data = NULL;
    program.vertexShader = NULL;
    shader = NULL;
}

static bool init_gpu(void)
{
    c3d_ready = C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    if (!c3d_ready) return false;

    inputs = linearAlloc(INPUT_SLOTS * FRAME_BYTES);
    padded = vramAlloc(TEX_W * CPS2_HEIGHT * sizeof(uint16_t));
    target = C3D_RenderTargetCreate(LCD_H, LCD_W, GPU_RB_RGB565, -1);
    if (!inputs || !padded || !target || !C3D_TexInitVRAM(&texture, TEX_W, TEX_H, GPU_RGB565))
        return false;
    shader = DVLB_ParseFile((u32 *)astra_quad_shader,
                            (const u8 *)astra_quad_shader_end - (const u8 *)astra_quad_shader);
    if (!shader || R_FAILED(shaderProgramInit(&program)) ||
        R_FAILED(shaderProgramSetVsh(&program, &shader->DVLE[0]))) return false;
    C3D_RenderTargetSetOutput(target, GFX_TOP, GFX_LEFT, RGB565_TRANSFER);
    C3D_BindProgram(&program);
    C3D_AttrInfo *attributes = C3D_GetAttrInfo();
    AttrInfo_Init(attributes);
    AttrInfo_AddLoader(attributes, 0, GPU_FLOAT, 4);
    AttrInfo_AddLoader(attributes, 1, GPU_FLOAT, 2);
    C3D_CullFace(GPU_CULL_NONE);
    C3D_DepthTest(false, GPU_ALWAYS, GPU_WRITE_COLOR);
    C3D_TexSetWrap(&texture, GPU_CLAMP_TO_EDGE, GPU_CLAMP_TO_EDGE);
    C3D_TexEnv *env = C3D_GetTexEnv(0);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_TEXTURE0, GPU_TEXTURE0);
    C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
    return true;
}

void display_init(void)
{
    gfxInit(GSP_RGB565_OES, GSP_RGB565_OES, false);
    consoleInit(GFX_BOTTOM, NULL);
    submitted = 0;
    display_set_view(false, VIEW_HORIZONTAL);
    gpu_ready = init_gpu();
    if (!gpu_ready) release_gpu();
}

void display_exit(void) { release_gpu(); }

bool display_is_accelerated(void) { return gpu_ready; }

void display_flush_console(void)
{
    GSPGPU_FlushDataCache(gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL),
                          320 * LCD_H * 2);
}

uint16_t *display_acquire(void)
{
    display_service();
    if (!gpu_ready) return writable = fallback;
    // Rendering a CPS2 frame has no dependency on the LCD swap. Keep the
    // pending image intact and never let the CPU modify the GPU's source.
    for (unsigned i = 0; i < INPUT_SLOTS; ++i) {
        uint16_t *slot = inputs + i * FRAME_PIXELS;
        if (slot != in_flight && slot != last_picture) return writable = slot;
    }
    return NULL;
}

static void vertex(float screen_x, float screen_y, float u, float v)
{
    // The upper framebuffer's physical axes are rotated relative to the LCD.
    C3D_ImmSendAttrib(screen_y, screen_x, -0.5f, 1.0f);
    C3D_ImmSendAttrib(u, v, 0.0f, 1.0f);
}

static void present_gpu(const uint16_t *source)
{
    // The core renders consecutive 384-pixel lines. TextureCopy inserts the
    // padding for a power-of-two texture without a CPU row copy; DisplayTransfer
    // then converts the 512-wide lines into PICA's 8x8 tiled RGB565 layout.
    GSPGPU_FlushDataCache((void *)source, FRAME_BYTES);
    const unsigned line_units = CPS2_WIDTH * 2 / 16;
    const unsigned gap_units = (TEX_W - CPS2_WIDTH) * 2 / 16;
    GX_TextureCopy((u32 *)source, GX_BUFFER_DIM(line_units, 0), (u32 *)padded,
                   GX_BUFFER_DIM(line_units, gap_units), FRAME_BYTES, GX_TRANSFER_RAW_COPY(1));
    GX_DisplayTransfer((u32 *)padded, GX_BUFFER_DIM(TEX_W, CPS2_HEIGHT),
                       (u32 *)texture.data, GX_BUFFER_DIM(TEX_W, CPS2_HEIGHT),
                       RGB565_TRANSFER | GX_TRANSFER_OUT_TILED(1));

    // Only the target linked to the upper LCD is submitted or swapped.
    C3D_RenderTargetClear(target, C3D_CLEAR_COLOR, 0, 0);
    C3D_FrameDrawOn(target);
    GPU_TEXTURE_FILTER_PARAM filter = native ? GPU_NEAREST : GPU_LINEAR;
    C3D_TexSetFilter(&texture, filter, filter);
    C3D_TexBind(0, &texture);
    float dx = (float)width / LCD_W, dy = (float)height / LCD_H;
    float u1 = (float)CPS2_WIDTH / TEX_W;
    // Keep the end samples on valid rows when vertically enlarging the image.
    float dv = native ? 0.0f : (0.5f - 0.5f * (CPS2_HEIGHT-1) / (height-1)) / TEX_H;
    float v1 = (float)CPS2_HEIGHT / TEX_H - dv;
    C3D_ImmDrawBegin(GPU_TRIANGLE_STRIP);
    // PICA's T axis rises from the texture's bottom; DMA wrote row zero first.
    float top = 1.0f-dv, bottom = 1.0f-v1;
    if (cabinet == VIEW_PORTRAIT) {
        vertex(dx,dy,u1,top); vertex(-dx,dy,u1,bottom);
        vertex(dx,-dy,0,top); vertex(-dx,-dy,0,bottom);
    } else if (cabinet == VIEW_DPAD_TOP) {
        vertex(dx,dy,u1,bottom); vertex(-dx,dy,0,bottom);
        vertex(dx,-dy,u1,top); vertex(-dx,-dy,0,top);
    } else {
        vertex(dx,dy,0,top); vertex(-dx,dy,u1,top);
        vertex(dx,-dy,0,bottom); vertex(-dx,-dy,u1,bottom);
    }
    C3D_ImmDrawEnd();
    // The input buffer was explicitly cleaned and vertices are in the command
    // list. Flushing only that list avoids an entire linear-heap flush.
    C3D_FrameEnd(GX_CMDLIST_FLUSH);
    frame_open = false;
}

static void present_software(const uint16_t *source)
{
    uint16_t *fb = (uint16_t *)gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    unsigned left = (LCD_W - width) / 2, top = (LCD_H - height) / 2;
    if (clear_buffers) memset(fb, 0, LCD_W * LCD_H * sizeof(*fb));
    for (unsigned x = 0; x < width; ++x) {
        uint16_t *dest = fb + (left+x) * LCD_H + (LCD_H-1-top);
        for (unsigned y = 0; y < height; ++y) {
            unsigned sx = source_x[x], sy = source_y[y];
            if (cabinet == VIEW_PORTRAIT) {
                dest[-(int)y] = source[sx*CPS2_WIDTH + CPS2_WIDTH-1-sy];
            } else {
                unsigned at = sy*CPS2_WIDTH+sx;
                dest[-(int)y] = source[cabinet == VIEW_DPAD_TOP ? FRAME_PIXELS-1-at : at];
            }
        }
    }
    if (clear_buffers) {
        GSPGPU_FlushDataCache(fb, LCD_W * LCD_H * sizeof(*fb));
        --clear_buffers;
    } else {
        GSPGPU_FlushDataCache(fb + left * LCD_H, width * LCD_H * sizeof(*fb));
    }
    gfxScreenSwapBuffers(GFX_TOP, false);
}

void display_present(const uint16_t *source)
{
    if (!source) return;
    if (source != writable) {
        uint16_t *dest = display_acquire();
        if (!dest) return;
        memcpy(dest, source, FRAME_BYTES);
        source = dest;
    }
    writable = NULL;
    // At most one completed CPU image can wait. If the game is temporarily
    // faster than scanout, show the newest image instead of building latency.
    last_picture = ready = source;
    display_service();
}

void display_redraw(void)
{
    ready = last_picture;
    display_service();
}

void display_service(void)
{
    if (!ready) return;
    if (gpu_ready && !frame_open) {
        if (!C3D_FrameBegin(C3D_FRAME_NONBLOCK)) return;
        frame_open = true;
        in_flight = NULL;
    }
    // The scanout buffers themselves are still double buffered. Only submit
    // the transfer once GSP has consumed the previous swap, even if we opened
    // the citro3d frame earlier while that swap was pending.
    if (gspIsPresentPending(GFX_TOP)) return;
    if (gpu_ready) {
        in_flight = ready;
        present_gpu(ready);
    } else present_software(ready);
    ready = NULL;
    ++submitted;
}

uint32_t display_submissions(void) { return submitted; }

void display_wait_until(uint64_t deadline)
{
    // The emulator would otherwise sleep this whole interval. Give the LCD
    // a chance to take the completed image without delaying the next CPU tick.
    for (;;) {
        display_service();
        u64 now = svcGetSystemTick();
        if (now >= deadline) return;
        u64 delay = deadline - now;
        const u64 retry = SYSCLOCK_ARM11 / 1000;
        if (ready && delay > retry) delay = retry;
        svcSleepThread((s64)(delay * 1000000000ULL / SYSCLOCK_ARM11));
        if (!ready) return;
    }
}
