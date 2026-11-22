#include "astra_text.h"
#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "cps2.h"
#include "display.h"

enum { ROWS = 8, LABEL = 40, SAVE = -2 };
typedef char Text[LABEL];

// Each entry owns two text rows (16 touch pixels). Primary actions can also
// be completed with the stylus alone, even if every physical key was remapped.
static int pick(const char *title, const char *detail, const Text *labels, int count,
                int selected, bool save, const char *hint)
{
    if (selected < 0 || selected >= count) selected = 0;
    bool dirty = true;
    while (aptMainLoop()) {
        int first = selected / ROWS * ROWS;
        if (dirty) {
            printf("\x1b[2J\x1b[1;1H\x1b[1;36m%.38s\x1b[0m\n%.39s\n", title, detail);
            for (int i = first; i < first + ROWS && i < count; ++i) {
                printf("\x1b[%d;1H%s%c %.36s\x1b[0m", 5 + 2*(i-first),
                       i == selected ? "\x1b[1;36m" : "", i == selected ? '>' : ' ', labels[i]);
            }
            printf("\x1b[22;1H%.39s\n", hint);
            printf(TXT_SETTINGS_NAV, first/ROWS+1, (count+ROWS-1)/ROWS);
            if (save) printf(TXT_START_SAVE);
            printf("\x1b[28;1H\x1b[1;36m%-10s%-10s%-10s%s\x1b[0m",
                   "  < PAGE", TXT_BACK, save ? TXT_SAVE : "", "  PAGE >");
            display_flush_console();
            dirty = false;
        }
        hidScanInput();
        u32 down = hidKeysDown(), move = down | hidKeysDownRepeat();
        if (down & KEY_B) return -1;
        if (save && (down & KEY_START)) return SAVE;
        if (down & KEY_A) return selected;
        if (down & KEY_TOUCH) {
            touchPosition tap;
            hidTouchRead(&tap);
            if (tap.py >= 216) {
                if (tap.px < 80) move |= KEY_LEFT;
                else if (tap.px < 160) return -1;
                else if (tap.px < 240) { if (save) return SAVE; }
                else move |= KEY_RIGHT;
            } else if (tap.py >= 32 && tap.py < 32 + ROWS * 16) {
                int touched = first + (tap.py - 32) / 16;
                if (touched < count) return touched;
            }
        }
        int next = selected;
        if (move & KEY_UP) next = (selected + count - 1) % count;
        else if (move & KEY_DOWN) next = (selected + 1) % count;
        else if (move & KEY_LEFT) next = selected > ROWS ? selected - ROWS : 0;
        else if (move & KEY_RIGHT) next = selected + ROWS < count ? selected + ROWS : count-1;
        dirty = next != selected;
        selected = next;
        display_service();
        gspWaitForVBlank();
    }
    return -1;
}

static bool save_problem(void)
{
    const Text options[] = {TXT_RETRY, TXT_CANCEL};
    return pick(TXT_SAVE_FAILED, TXT_CHECK_SD, options,
                2, 0, false, TXT_STILL_PAUSED) == 0;
}

void settings_edit(int game, Bindings *active)
{
    const char *id = cps2_game_id(game);
    const int actions = cps2_game_buttons(game);
    Bindings draft = *active;
    int row = 0;
    for (;;) {
        Text keys[BIND_SLOT_COUNT + 1];
        for (int i = 0; i < BIND_SLOT_COUNT; ++i)
            snprintf(keys[i], LABEL, "%-11s %.24s", bindings_key_name(i),
                     bindings_action_name(draft.action[i], game));
        strcpy(keys[BIND_SLOT_COUNT], TXT_DEFAULT_BUTTONS);
        row = pick(TXT_CONTROLS_TITLE, cps2_game_title(game), keys, BIND_SLOT_COUNT + 1,
                   row, true, TXT_PICK_BUTTON);
        if (row == SAVE) {
            if (memcmp(&draft, active, sizeof(draft)) == 0) return;
            while (!bindings_save(&draft, id)) if (!save_problem()) return;
            *active = draft;
            return;
        }
        if (row < 0) return;
        if (row == BIND_SLOT_COUNT) {
            bindings_defaults(&draft, actions);
            continue;
        }
        Text choices[BIND_ACTION_COUNT];
        BindAction map[BIND_ACTION_COUNT];
        int n = 0, selected = 0;
        for (int a = 0; a < BIND_ACTION_COUNT; ++a) {
            if (!bindings_allowed((BindAction)a, actions)) continue;
            if (a == draft.action[row]) selected = n;
            map[n] = (BindAction)a;
            snprintf(choices[n++], LABEL, "%s", bindings_action_name((BindAction)a, game));
        }
        int value = pick(TXT_ASSIGN, bindings_key_name(row), choices, n,
                         selected, false, TXT_PICK_ACTION);
        if (value >= 0) draft.action[row] = map[value];
    }
}
