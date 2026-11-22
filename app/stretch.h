#pragma once
#include <stdint.h>
#include "cps2.h"

typedef struct {
    int16_t history[4 * CPS2_MAX_SAMPLES];
    unsigned previous;
    int debt;
} AudioStretch;

// Output capacity is three times the input length, in stereo pairs.
unsigned stretch_audio(AudioStretch *s, const int16_t *input, unsigned pairs,
                       unsigned extra, int16_t *output);
