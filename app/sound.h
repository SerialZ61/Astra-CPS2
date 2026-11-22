#pragma once
#include <stdbool.h>
#include <stdint.h>

bool sound_open(void);
bool sound_needs_refill(void);
void sound_wait_for_slot(void);
void sound_submit(const int16_t *pcm, unsigned pairs, bool continuous);
void sound_reset(void);
void sound_close(void);
unsigned sound_underruns(void);
unsigned sound_drops(void);
