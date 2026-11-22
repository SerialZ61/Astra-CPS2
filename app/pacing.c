#include "pacing.h"

enum { FULL = 65536 };

void pacing_reset(FramePacer *p, uint32_t period)
{
    *p = (FramePacer){ .period = period };
}

bool pacing_wants_draw(FramePacer *p, enum video_mode mode, uint64_t now)
{
    if (mode == VIDEO_ALL) return true;
    if (mode == VIDEO_30) {
        // This is a wall-clock presentation target. The arcade CPU and
        // sound still advance on every loop, also between two screen slots.
        if (p->next_slot && now + p->period / 12 < p->next_slot) return false;
        const uint64_t step = 2 * (uint64_t)p->period;
        if (!p->next_slot || now >= p->next_slot + step) p->next_slot = now + step;
        else p->next_slot += step;
        return true;
    }

    // Average cost at a drawing fraction f: plain + f * (drawn - plain).
    // Reserve a small margin for input, scheduling and the OS. Distribute
    // fractional rates across arcade frames instead of accumulating old debt.
    const uint32_t budget = p->period - p->period / 32;
    uint32_t fraction = FULL;
    if (p->drawn_cost > budget) {
        if (!p->plain_cost) fraction = FULL / 2; // Measure one non-rendered tick.
        else if (p->plain_cost >= budget) fraction = FULL / 4;
        else {
            fraction = (uint64_t)(budget - p->plain_cost) * FULL /
                       (p->drawn_cost - p->plain_cost);
            if (fraction < FULL / 4) fraction = FULL / 4;
        }
    }
    p->credit += fraction;
    // Keep less than two frames of credit after long external interruptions.
    if (p->credit >= FULL * 2) p->credit = FULL * 2 - 1;
    return p->credit >= FULL;
}

void pacing_record(FramePacer *p, bool drawn, uint32_t elapsed)
{
    // A suspend or a single long system stall must not skew future cadence.
    if (elapsed > p->period * 8) elapsed = p->period * 8;
    uint32_t *estimate = drawn ? &p->drawn_cost : &p->plain_cost;
    if (*estimate) *estimate = (*estimate * 7 + elapsed) / 8;
    else *estimate = elapsed;
    if (drawn && p->credit >= FULL) p->credit -= FULL;
}
