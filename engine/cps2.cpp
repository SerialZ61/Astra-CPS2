#include "astra_text.h"
#include "cps2.h"
#include "cps.h"
#include "romzip.h"

// A fixed linear heap leaves the rest of the title memory for large CPS2 graphics.
// LCD buffers, GPU uploads and the audio queue all fit inside this budget.
extern "C" { uint32_t __ctru_linear_heap_size = 4 * 1024 * 1024; }

const BurnDriver *astra_driver(int index);
extern const char *cpsLoadStage;
extern unsigned cpsLoadBytes;
extern "C" uint32_t __ctru_heap_size;
void astraWaitOpen();
void astraWaitClose();

namespace {
int current = -1;
unsigned sampleRemainder;
int16_t discardAudio[2 * CPS2_MAX_SAMPLES];
char message[256];
const char *const tags[] = {
    "p1 coin", "p1 start", "p1 up", "p1 down", "p1 left", "p1 right",
    "p1 fire 1", "p1 fire 2", "p1 fire 3", "p1 fire 4", "p1 fire 5", "p1 fire 6"
};
constexpr unsigned inputCount = sizeof(tags) / sizeof(tags[0]);
unsigned char *inputs[inputCount];
unsigned short *paddle;

unsigned rgb565(int red, int green, int blue, int)
{
    return ((red & 0xf8) << 8) | ((green & 0xfc) << 3) | (blue >> 3);
}

void bindInputs()
{
    BurnInputInfo input;
    memset(inputs, 0, sizeof(inputs));
    paddle = nullptr;
    for (unsigned i = 0; !BurnDrvGetInputInfo(&input, i); ++i) {
        if (!input.szInfo) continue;
        if (input.nType == BIT_ANALOG_REL && !strcmp(input.szInfo, "mouse x-axis"))
            paddle = input.pShortVal;
        if (input.nType != BIT_DIGITAL) continue;
        for (unsigned j = 0; j < inputCount; ++j)
            if (!strcmp(input.szInfo, tags[j])) inputs[j] = input.pVal;
    }
}
}

const char *cps2_game_button_label(int game, unsigned number)
{
    const BurnDriver *driver = astra_driver(game);
    if (!driver || !number || number > 6) return nullptr;
    BurnInputInfo input;
    const char *tag = tags[5 + number];
    for (unsigned i = 0; !driver->GetInputInfo(&input, i); ++i)
        if (input.nType == BIT_DIGITAL && input.szInfo && !strcmp(input.szInfo, tag))
            return input.szName;
    return nullptr;
}

int cps2_open_game(int requested, const char *path)
{
    cps2_close();
    message[0] = 0;
    const int game = romzip_prepare(path, requested, message, sizeof(message));
    if (game < 0) return 1;
    BurnLibInit();
    nBurnDrvSelect = game;
    bForce60Hz = false;
    nBurnSoundRate = CPS2_SAMPLE_RATE;
    nBurnSoundLen = CPS2_MAX_SAMPLES;
    nBurnBpp = 2;
    nBurnPitch = CPS2_WIDTH * sizeof(uint16_t);
    BurnHighCol = rgb565;
    BurnExtLoadRom = romzip_load;
    nCurrentFrame = 0;
    sampleRemainder = 0;
    cpsLoadStage = TXT_INIT_DRIVER;
    cpsLoadBytes = 0;
    int result = BurnDrvInit();
    BurnExtLoadRom = NULL;
    romzip_release();
    if (result) {
        BurnDrvExit();
        BurnLibExit();
        if (romzip_error()[0]) snprintf(message, sizeof(message), "%s", romzip_error());
        else if (cpsLoadBytes)
            snprintf(message, sizeof(message), TXT_BLOCK_SIZE,
                     cpsLoadStage, cpsLoadBytes / 1024, (unsigned long)(__ctru_heap_size / 1024));
        else snprintf(message, sizeof(message), TXT_INIT_FAILED,
                      cpsLoadStage, (unsigned long)(__ctru_heap_size / 1024));
        return 1;
    }
    current = game;
    astraWaitOpen();
    bindInputs();
    BurnRecalcPal();
    return 0;
}

int cps2_open(const char *path) { return cps2_open_game(-1, path); }
const char *cps2_error() { return message; }
int cps2_current_game() { return current; }
void cps2_reset() { if (current >= 0) CpsReset = 1; }

int cps2_frame(uint32_t buttons, uint16_t *video, int16_t *audio)
{
    if (current < 0) return -1;
    for (unsigned i = 0; i < inputCount; ++i)
        if (inputs[i]) *inputs[i] = (buttons >> i) & 1;

    if (paddle) {
        int right = (buttons & CPS2_RIGHT) != 0;
        int left = (buttons & CPS2_LEFT) != 0;
        *paddle = static_cast<unsigned short>((right - left) * 0x400);
    }
    sampleRemainder += CPS2_SAMPLE_RATE * CPS2_FPS_DEN;
    nBurnSoundLen = sampleRemainder / CPS2_FPS_NUM;
    sampleRemainder %= CPS2_FPS_NUM;
    pBurnSoundOut = audio ? audio : discardAudio;
    pBurnDraw = reinterpret_cast<unsigned char *>(video);
    const int result = BurnDrvFrame();
    CpsReset = 0;
    if (result) {
        snprintf(message, sizeof(message), TXT_EMULATION_ERROR);
        return -1;
    }
    ++nCurrentFrame;
    return nBurnSoundLen;
}

void cps2_close()
{
    if (current >= 0) {
        astraWaitClose();
        BurnDrvExit();
        BurnLibExit();
        current = -1;
    }
    pBurnSoundOut = NULL;
    pBurnDraw = NULL;
    CpsReset = 0;
}
