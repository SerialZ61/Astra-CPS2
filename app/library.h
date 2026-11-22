#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char *path;
    /* Nonnegative indices name a registered driver. Negative entries can
       still be opened by chip contents (including an arbitrarily renamed ZIP). */
    int game;
} RomEntry;

enum { LIBRARY_UNKNOWN = -1, LIBRARY_UNMATCHED = -2 };

typedef struct {
    RomEntry *entries;
    size_t count, capacity;
    bool incomplete;
} RomLibrary;

void library_scan(RomLibrary *library);
void library_free(RomLibrary *library);
int library_game_for_path(const char *path);
const char *library_filename(const char *path);
const char *library_parent_hint(const RomEntry *entry);
int library_next_family(const RomLibrary *library, int selected, int step);
bool library_reference_game(int game);
