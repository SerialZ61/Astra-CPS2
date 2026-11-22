#pragma once
#include <stdbool.h>
#include <stdint.h>

enum video_mode { VIDEO_AUTO, VIDEO_30, VIDEO_ALL, VIDEO_MODE_COUNT };

typedef struct {
    uint32_t period, drawn_cost, plain_cost, credit;
    uint64_t next_slot;
} FramePacer;

void pacing_reset(FramePacer *pacer, uint32_t period);
bool pacing_wants_draw(FramePacer *pacer, enum video_mode mode, uint64_t now);
void pacing_record(FramePacer *pacer, bool drawn, uint32_t elapsed);
