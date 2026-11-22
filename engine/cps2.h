#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    CPS2_WIDTH = 384, CPS2_HEIGHT = 224,
    CPS2_SAMPLE_RATE = 22050, CPS2_MAX_SAMPLES = 370,
    CPS2_FPS_NUM = 5963, CPS2_FPS_DEN = 100
};
enum {
    CPS2_COIN = 1u << 0, CPS2_START = 1u << 1,
    CPS2_UP = 1u << 2, CPS2_DOWN = 1u << 3,
    CPS2_LEFT = 1u << 4, CPS2_RIGHT = 1u << 5,
    CPS2_ATTACK = 1u << 6, CPS2_JUMP = 1u << 7,
    CPS2_BUTTON3 = 1u << 8, CPS2_BUTTON4 = 1u << 9,
    CPS2_BUTTON5 = 1u << 10, CPS2_BUTTON6 = 1u << 11
};

/* Catalogue pointers refer to static data. Invalid indices return NULL/zero. */
int cps2_game_count(void);
/* Filename hints for older ROM set naming conventions. Pass a basename
 * without ".zip". Actual chip sizes and CRCs decide what can run. */
int cps2_archive_game(const char *stem);
const char *cps2_archive_parent(const char *stem);
const char *cps2_game_id(int game);
const char *cps2_game_title(int game);
const char *cps2_game_parent(int game);
int cps2_game_buttons(int game);
const char *cps2_game_button_label(int game, unsigned number);
int cps2_game_vertical(int game);
int cps2_game_chip(int game, unsigned chip, const char **name, uint32_t *bytes, uint32_t *crc);
/* -1 automatically identifies the game by its program and data chips. */
int cps2_open_game(int game, const char *path);
int cps2_current_game(void);
/* Pulse the emulated board's reset input on the next frame. */
void cps2_reset(void);
/* Opens the supplied ZIP read-only. Returns zero on success. */
int cps2_open(const char *path);
const char *cps2_error(void);
/* One CPS2 video period. A null video skips rendering. For PCM output,
 * supply space for CPS2_MAX_SAMPLES stereo pairs. Returns stereo pairs
 * produced, or -1 on error. Either output buffer may be null. */
int cps2_frame(uint32_t buttons, uint16_t *rgb565, int16_t *stereo);
/* Elapsed ARM11 ticks inside the arcade draw call on the last frame. */
void cps2_set_draw_profiling(bool enabled);
uint32_t cps2_draw_ticks(void);
void cps2_close(void);

#ifdef __cplusplus
}
#endif
