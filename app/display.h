#pragma once
#include <stdbool.h>
#include <stdint.h>
void display_init(void);
void display_exit(void);
bool display_is_accelerated(void);
enum cabinet_view { VIEW_HORIZONTAL, VIEW_PORTRAIT, VIEW_DPAD_TOP, VIEW_DPAD_BOTTOM };
void display_set_view(bool native, enum cabinet_view view);
uint32_t display_directions(uint32_t buttons, enum cabinet_view view);
// Write the next CPS2 picture into this buffer, then hand it to display_present.
uint16_t *display_acquire(void);
void display_present(const uint16_t *source);
void display_service(void);
void display_redraw(void);
void display_wait_until(uint64_t tick_deadline);
uint32_t display_submissions(void);
void display_flush_console(void);
