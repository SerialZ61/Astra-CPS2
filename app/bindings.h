#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    BIND_NONE, BIND_UP, BIND_DOWN, BIND_LEFT, BIND_RIGHT, BIND_COIN, BIND_START,
    BIND_1, BIND_2, BIND_3, BIND_4, BIND_5, BIND_6, BIND_COMBO,
    BIND_PAUSE, BIND_RATE, BIND_FORMAT, BIND_ACTION_COUNT
} BindAction;

enum { BIND_SLOT_COUNT = 16 };
typedef struct { uint8_t action[BIND_SLOT_COUNT]; } Bindings;

void bindings_defaults(Bindings *map, int actions);
bool bindings_load(Bindings *map, const char *game, int actions);
bool bindings_save(const Bindings *map, const char *game);
uint32_t bindings_buttons(const Bindings *map, uint32_t held);
bool bindings_pressed(const Bindings *map, BindAction action, uint32_t down);
const char *bindings_key_name(int slot);
const char *bindings_action_name(BindAction action, int game);
bool bindings_allowed(BindAction action, int actions);

/* Fixed-size records per driver. Pass the extension without its dot.
 * Failed reads leave the destination untouched. */
bool profile_read(const char *game, const char *ext, void *bytes, size_t size);
bool profile_write(const char *game, const char *ext, const void *bytes, size_t size);
