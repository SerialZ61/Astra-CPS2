#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    float seconds, game_fps, displayed_fps;
    unsigned empty, full;
} Measurement;

bool measurement_append(const Measurement *window, const char *archive, int game,
                        const char *cadence, bool audio, bool continuous);
void record_load_error(const char *archive, const char *reason);

// Elapsed ARM11 system ticks. The game's CPU draw is part of core_ticks.
// wait_ticks includes pending display service during the pacing wait.
typedef struct {
    uint64_t duration, core_ticks, draw_ticks, video_ticks, sound_ticks;
    uint64_t audio_wait_ticks, wait_ticks, max_core_ticks;
    unsigned frames, drawn, submitted, empty, full;
} ProfileWindow;

bool profile_append_capture(const ProfileWindow *rows, unsigned count, uint32_t tick_rate,
                            const char *archive, int game, const char *cadence,
                            bool audio, bool continuous, bool gpu);
