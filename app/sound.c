#include <3ds.h>
#include <string.h>
#include "cps2.h"
#include "sound.h"
#include "stretch.h"

// Each NDSP submission starts on its own cache line.
enum { SLOTS = 9, BASE_PREFILL = 4, MAX_PREFILL = 6, WINDOW = 8,
       STRIDE = (CPS2_MAX_SAMPLES * 12 + 31) & ~31 };
static ndspWaveBuf waves[SLOTS];
static uint8_t *pool;
static unsigned next_slot, primed, target, underruns, drops;
static AudioStretch stretch;
static u64 last_tick;
static int interval_q8;
static int intervals[WINDOW], total_q8;
static unsigned window_count, window_slot;

bool sound_open(void)
{
    if (R_FAILED(ndspInit())) return false;
    pool = linearAlloc(SLOTS * STRIDE);
    if (!pool) {
        ndspExit();
        return false;
    }
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnReset(0);
    ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
    ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
    ndspChnSetRate(0, CPS2_SAMPLE_RATE);
    float mix[12] = {1.0f, 1.0f};
    ndspChnSetMix(0, mix);
    for (unsigned i = 0; i < SLOTS; ++i)
        waves[i].data_vaddr = pool + i * STRIDE;
    sound_reset();
    return true;
}

void sound_reset(void)
{
    if (!pool) return;
    ndspChnSetPaused(0, true);
    ndspChnWaveBufClear(0);
    next_slot = primed = 0;
    target = BASE_PREFILL;
    stretch.previous = 0;
    stretch.debt = 0;
    interval_q8 = CPS2_MAX_SAMPLES * 256;
    last_tick = 0;
    window_count = window_slot = total_q8 = 0;
}

static bool occupied(const ndspWaveBuf *w)
{
    return w->status == NDSP_WBUF_QUEUED || w->status == NDSP_WBUF_PLAYING;
}

bool sound_needs_refill(void)
{
    if (!pool || primed < target) return false;
    unsigned active = 0;
    for (unsigned i = 0; i < SLOTS; ++i) active += occupied(&waves[i]);
    return active + 1 < target;
}

void sound_wait_for_slot(void)
{
    if (!pool || !occupied(&waves[next_slot])) return;
    // A small clock mismatch must not discard the next piece of music.
    // The longest stretched block is just over 50 ms.
    u64 limit = svcGetSystemTick() + SYSCLOCK_ARM11 / 16;
    while (occupied(&waves[next_slot]) && svcGetSystemTick() < limit)
        svcSleepThread(500000);
}

void sound_submit(const int16_t *pcm, unsigned pairs, bool continuous)
{
    if (!pool || !pairs || pairs > CPS2_MAX_SAMPLES) return;
    unsigned prev = (next_slot + SLOTS - 1) % SLOTS;
    if (primed == target && waves[prev].status == NDSP_WBUF_DONE) {
        ++underruns;
        ndspChnSetPaused(0, true);
        primed = 0;
        if (target < MAX_PREFILL) ++target;
    }
    ndspWaveBuf *w = &waves[next_slot];
    if (w->status == NDSP_WBUF_QUEUED || w->status == NDSP_WBUF_PLAYING) {
        ++drops;
        return;
    }
    int16_t *dest = (int16_t *)(pool + next_slot * STRIDE);
    u64 now = svcGetSystemTick();
    if (continuous) {
        if (last_tick) {
            u64 elapsed = now - last_tick;
            if (elapsed > SYSCLOCK_ARM11 / 20) elapsed = SYSCLOCK_ARM11 / 20;
            int measured = elapsed * CPS2_SAMPLE_RATE * 256 / SYSCLOCK_ARM11;
            unsigned active = 0;
            for (unsigned i = 0; i < SLOTS; ++i) active += occupied(&waves[i]);
            if (active > target && measured > (int)pairs * 256) measured = pairs * 256;
            // Average complete submission intervals so an expensive draw and
            // the quick skipped tick after it are measured together.
            if (window_count == WINDOW) total_q8 -= intervals[window_slot];
            else ++window_count;
            intervals[window_slot] = measured;
            total_q8 += measured;
            window_slot = (window_slot + 1) % WINDOW;
            interval_q8 = total_q8 / (int)window_count;
            // A scene can get slower before the moving average catches up.
            // Restore a small margin while the last one or two blocks play.
            if (primed == target && active <= 2) {
                int minimum = (int)pairs * 256;
                if (interval_q8 < minimum) interval_q8 = minimum;
                interval_q8 += (3 - active) * (24 * 256);
            }
        }
        int extra = interval_q8 / 256 - (int)pairs;
        pairs = stretch_audio(&stretch, pcm, pairs, extra > 4 ? (unsigned)extra : 0, dest);
        last_tick = now;
    } else {
        memcpy(dest, pcm, pairs * 4);
        last_tick = 0;
        window_count = window_slot = total_q8 = 0;
        interval_q8 = pairs * 256;
        stretch.previous = 0;
        stretch.debt = 0;
    }
    DSP_FlushDataCache(pool + next_slot * STRIDE, pairs * 4);
    w->nsamples = pairs;
    ndspChnWaveBufAdd(0, w);
    next_slot = (next_slot + 1) % SLOTS;
    if (primed < target && ++primed == target)
        ndspChnSetPaused(0, false);
}

unsigned sound_underruns(void) { return underruns; }
unsigned sound_drops(void) { return drops; }

void sound_close(void)
{
    if (!pool) return;
    ndspChnWaveBufClear(0);
    ndspExit();
    linearFree(pool);
    pool = NULL;
}
