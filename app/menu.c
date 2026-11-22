#include "astra_text.h"
#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "display.h"
#include "cps2.h"

enum { PAGE_SIZE = 7 };

static int first_other_zip(const RomLibrary *library)
{
    int index = 0;
    while ((size_t)index < library->count && library->entries[index].game >= 0) ++index;
    return index;
}

static void paint_menu(const RomLibrary *library, int selected)
{
    printf(TXT_LIBRARY_HEADER);
    if (!library->count) {
        printf(TXT_ROM_FOLDER);
    } else {
        int first = selected / PAGE_SIZE * PAGE_SIZE;
        for (int i = first; i < first + PAGE_SIZE && (size_t)i < library->count; ++i) {
            const RomEntry *rom = &library->entries[i];
            const char *title = rom->game < 0 ? library_filename(rom->path) : cps2_game_title(rom->game);
            char mark = library_reference_game(rom->game) ? '*' : rom->game < 0 ? '?' : ' ';
            printf("%s%c%c %.36s\x1b[0m\n", i == selected ? "\x1b[1;36m" : "",
                   i == selected ? '>' : ' ', mark, title);
        }
        const RomEntry *rom = &library->entries[selected];
        printf("\x1b[11;1H%s   %u / %u\n", rom->game >= 0 ? TXT_SUPPORTED : TXT_OTHER_ARCHIVES,
               (unsigned)(selected + 1), (unsigned)library->count);
        if (rom->game >= 0) {
            const char *title = cps2_game_title(rom->game);
            for (size_t off = 0; off < strlen(title) && off < 114; off += 38)
                printf("%.38s\n", title + off);
        }
        printf("\x1b[15;1H%.39s\n", library_filename(rom->path));
        if (library_reference_game(rom->game)) printf(TXT_REFERENCE_GAME);
        else if (rom->game == LIBRARY_UNMATCHED) printf(TXT_NO_DRIVER);
        else if (rom->game < 0) printf(TXT_UNKNOWN_NAME);
        else printf(TXT_INCLUDED_DRIVER);
        const char *parent = library_parent_hint(rom);
        if (parent && *parent) printf(TXT_PARENT_HINT, parent);
    }
    if (library->incomplete) printf(TXT_INCOMPLETE_LIST);
    printf(TXT_NAVIGATION);
    printf(TXT_FAMILY_KEYS);
    int other = first_other_zip(library);
    if (other > 0 && (size_t)other < library->count)
        printf("Y              %s", selected < other ? TXT_SHOW_OTHER : TXT_SHOW_SUPPORTED);
    printf(TXT_LIBRARY_ACTIONS);
    printf("\x1b[29;1H\x1b[1;36m%-14s%-13s%s\x1b[0m", "  < PAGE", TXT_PLAY_BUTTON, "  PAGE >");
    display_flush_console();
}

int menu_choose(RomLibrary *library, int selected)
{
    if (selected < 0 || (size_t)selected >= library->count) selected = 0;
    hidSetRepeatParameters(20, 5);
    bool dirty = true;
    while (aptMainLoop()) {
        if (dirty) paint_menu(library, selected);
        dirty = false;
        hidScanInput();
        u32 down = hidKeysDown(), move = down | hidKeysDownRepeat();
        if (down & KEY_B) break;
        if ((down & KEY_A) && library->count) return selected;
        if ((down & KEY_TOUCH) && library->count) {
            touchPosition tap;
            hidTouchRead(&tap);
            if (tap.py >= 216) {
                if (tap.px < 106) move |= KEY_LEFT;
                else if (tap.px >= 213) move |= KEY_RIGHT;
                else return selected;
            } else if (tap.py >= 16 && tap.py < (2 + PAGE_SIZE) * 8) {
                int index = selected / PAGE_SIZE * PAGE_SIZE + tap.py / 8 - 2;
                if ((size_t)index < library->count) {
                    selected = index;
                    dirty = true;
                }
            }
        }
        if (down & KEY_X) {
            library_scan(library);
            selected = 0;
            dirty = true;
        } else if (library->count) {
            int next = selected, count = (int)library->count;
            if (move & KEY_UP) next = (selected + count - 1) % count;
            else if (move & KEY_DOWN) next = (selected + 1) % count;
            else if (move & KEY_LEFT) next = selected > PAGE_SIZE ? selected - PAGE_SIZE : 0;
            else if (move & KEY_RIGHT) next = selected + PAGE_SIZE < count ? selected + PAGE_SIZE : count - 1;
            else if (down & KEY_L) next = library_next_family(library, selected, -1);
            else if (down & KEY_R) next = library_next_family(library, selected, 1);
            else if (down & KEY_Y) {
                int other = first_other_zip(library);
                if (other > 0 && other < count) next = selected < other ? other : 0;
            }
            dirty |= next != selected;
            selected = next;
        }
        display_service();
        gspWaitForVBlank();
    }
    return -1;
}

void menu_error(const char *path, const char *reason)
{
    printf(TXT_LOAD_HEADER);
    printf(TXT_BACK_TO_GAMES, library_filename(path), reason);
    display_flush_console();
    while (aptMainLoop()) {
        hidScanInput();
        if (hidKeysDown() & (KEY_A | KEY_B)) return;
        display_service();
        gspWaitForVBlank();
    }
}
