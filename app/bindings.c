#include "astra_text.h"
#include "bindings.h"
#include "cps2.h"
#include <3ds/types.h>
#include <3ds/services/hid.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static const struct { const char *name; uint32_t key; } slots[BIND_SLOT_COUNT] = {
    {"A", KEY_A}, {"B", KEY_B}, {"X", KEY_X}, {"Y", KEY_Y}, {"L", KEY_L}, {"R", KEY_R},
    {"START", KEY_START}, {"SELECT", KEY_SELECT},
    {TXT_DPAD_UP, KEY_DUP}, {TXT_DPAD_DOWN, KEY_DDOWN},
    {TXT_DPAD_LEFT, KEY_DLEFT}, {TXT_DPAD_RIGHT, KEY_DRIGHT},
    {TXT_PAD_UP, KEY_CPAD_UP}, {TXT_PAD_DOWN, KEY_CPAD_DOWN},
    {TXT_PAD_LEFT, KEY_CPAD_LEFT}, {TXT_PAD_RIGHT, KEY_CPAD_RIGHT}
};
static const uint16_t arcade[BIND_ACTION_COUNT] = {
    [BIND_UP] = CPS2_UP, [BIND_DOWN] = CPS2_DOWN, [BIND_LEFT] = CPS2_LEFT,
    [BIND_RIGHT] = CPS2_RIGHT, [BIND_COIN] = CPS2_COIN, [BIND_START] = CPS2_START,
    [BIND_1] = CPS2_ATTACK, [BIND_2] = CPS2_JUMP, [BIND_3] = CPS2_BUTTON3,
    [BIND_4] = CPS2_BUTTON4, [BIND_5] = CPS2_BUTTON5, [BIND_6] = CPS2_BUTTON6,
    [BIND_COMBO] = CPS2_ATTACK | CPS2_JUMP
};

void bindings_defaults(Bindings *map, int actions)
{
    *map = (Bindings){{ BIND_1, BIND_2, BIND_COMBO, BIND_PAUSE, BIND_RATE, BIND_FORMAT,
        BIND_START, BIND_COIN, BIND_UP, BIND_DOWN, BIND_LEFT, BIND_RIGHT,
        BIND_UP, BIND_DOWN, BIND_LEFT, BIND_RIGHT }};
    if (actions == 3) map->action[2] = BIND_3;
    if (actions == 4 || actions == 5) {
        map->action[2] = BIND_3;
        map->action[3] = BIND_4;
        if (actions == 5) map->action[4] = BIND_5;
    } else if (actions >= 6) {
        const uint8_t fighter[] = {BIND_5, BIND_4, BIND_2, BIND_1, BIND_3, BIND_6};
        memcpy(map->action, fighter, sizeof(fighter));
    }
    for (int i = 0; i < BIND_SLOT_COUNT; ++i)
        if (!bindings_allowed((BindAction)map->action[i], actions)) map->action[i] = BIND_NONE;
}

bool bindings_allowed(BindAction action, int actions)
{
    if ((unsigned)action >= BIND_ACTION_COUNT) return false;
    if (action >= BIND_1 && action <= BIND_6) return (int)(action - BIND_1) < actions;
    return action != BIND_COMBO || actions >= 2;
}

const char *bindings_key_name(int slot)
{
    return (unsigned)slot < BIND_SLOT_COUNT ? slots[slot].name : "";
}

const char *bindings_action_name(BindAction action, int game)
{
    static const char *const labels[] = { TXT_NONE, TXT_UP, TXT_DOWN, TXT_LEFT, TXT_RIGHT,
        TXT_COIN, TXT_START_GAME, "Action 1", "Action 2", "Action 3", "Action 4", "Action 5",
        "Action 6", "Actions 1+2", "Pause", TXT_CHANGE_RATE, TXT_FORMAT };
#ifndef ASTRA_ENGLISH
    static const struct { const char *driver, *label; } names[] = {
        {"Weak punch", "Poing leger"}, {"Medium punch", "Poing moyen"}, {"Strong punch", "Poing fort"},
        {"Weak kick", "Pied leger"}, {"Medium kick", "Pied moyen"}, {"Strong kick", "Pied fort"},
        {"Hold", "Prise"}, {"Punch", "Poing"}, {"Kick", "Pied"}, {"Special", "Coup special"},
        {"Low Attack", "Attaque basse"}, {"High Attack", "Attaque haute"},
        {"Boost", "Propulsion"}, {"Weapon", "Arme"}, {"Attack", "Attaque"}, {"Jump", "Saut"},
        {"Shot", "Tir"}, {"Bomb", "Bombe"}, {"Shot (auto)", "Tir auto"}, {"Auto", "Tir auto"},
        {"Shot1", "Tir 1"}, {"Shot2", "Tir 2"}, {"Shot3", "Tir 3"},
        {"Select", "Selection"}, {"Use", "Utiliser"}, {"Turn 1", "Rotation 1"}, {"Turn 2", "Rotation 2"},
        {"Rotate Left", "Rotation gauche"}, {"Rotate Right", "Rotation droite"},
        {"Answer 1", "Reponse 1"}, {"Answer 2", "Reponse 2"}, {"Answer 3", "Reponse 3"}, {"Answer 4", "Reponse 4"}
    };
#endif
    if ((unsigned)action >= BIND_ACTION_COUNT) return "";
    if (action >= BIND_1 && action <= BIND_6) {
        const char *name = cps2_game_button_label(game, 1u + action - BIND_1);
        if (name && !strncmp(name, "P1 ", 3)) name += 3;
#ifdef ASTRA_ENGLISH
        if (name && *name) return name;
#else
        for (size_t i = 0; name && i < sizeof(names)/sizeof(*names); ++i)
            if (!strcmp(names[i].driver, name)) return names[i].label;
#endif
    }
    return labels[action];
}

uint32_t bindings_buttons(const Bindings *map, uint32_t held)
{
    uint32_t result = 0;
    for (int i = 0; i < BIND_SLOT_COUNT; ++i) {
        unsigned action = map->action[i];
        if ((held & slots[i].key) && action < BIND_ACTION_COUNT) result |= arcade[action];
    }
    return result;
}

bool bindings_pressed(const Bindings *map, BindAction action, uint32_t down)
{
    if (!down || action == BIND_NONE || (unsigned)action >= BIND_ACTION_COUNT) return false;
    for (int i = 0; i < BIND_SLOT_COUNT; ++i)
        if ((down & slots[i].key) && map->action[i] == action) return true;
    return false;
}

#define CONFIG_DIR "sdmc:/3ds/AstraCPS2/config"
typedef struct { char path[112], backup[120], temp[120]; } ProfileFiles;

static bool valid_component(const char *value, size_t limit)
{
    if (!value || !*value) return false;
    size_t i = 0;
    for (; value[i] && i < limit; ++i) {
        char c = value[i];
        if (!(c >= 'a' && c <= 'z') && !(c >= '0' && c <= '9') && c != '_') return false;
    }
    return !value[i];
}

static bool file_names(ProfileFiles *f, const char *game, const char *ext)
{
    if (!valid_component(game, 48) || !valid_component(ext, 8)) return false;
    snprintf(f->path, sizeof(f->path), CONFIG_DIR "/%s.%s", game, ext);
    snprintf(f->backup, sizeof(f->backup), "%s.bak", f->path);
    snprintf(f->temp, sizeof(f->temp), "%s.tmp", f->path);
    return true;
}

/* Check the size and digest before accepting a saved key map. */
static uint32_t digest(const uint8_t *data, size_t size)
{
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < size; ++i) hash = (hash ^ data[i]) * 16777619u;
    return hash;
}

typedef struct { char magic[4]; uint32_t size, digest; } RecordHeader;

static bool read_record(const char *path, void *bytes, size_t size)
{
    FILE *f = fopen(path, "rb");
    if (!f) return false;
    RecordHeader h;
    bool ok = fread(&h, 1, sizeof(h), f) == sizeof(h) && !memcmp(h.magic, "APF1", 4)
           && h.size == size && fread(bytes, 1, size, f) == size
           && fgetc(f) == EOF && !ferror(f) && h.digest == digest(bytes, size);
    fclose(f);
    return ok;
}

bool profile_read(const char *game, const char *ext, void *bytes, size_t size)
{
    ProfileFiles f;
    if (!bytes || !size || !file_names(&f, game, ext)) return false;
    void *scratch = malloc(size);
    if (!scratch) return false;
    bool ok = read_record(f.path, scratch, size) || read_record(f.backup, scratch, size)
           || read_record(f.temp, scratch, size);
    if (ok) memcpy(bytes, scratch, size);
    free(scratch);
    return ok;
}

static bool make_dir(const char *path) { return mkdir(path, 0777) == 0 || errno == EEXIST; }
static bool discard(const char *path) { return remove(path) == 0 || errno == ENOENT; }

bool profile_write(const char *game, const char *ext, const void *bytes, size_t size)
{
    ProfileFiles f;
    if (!bytes || !size || !file_names(&f, game, ext)) return false;
    if (!make_dir("sdmc:/3ds") || !make_dir("sdmc:/3ds/AstraCPS2") || !make_dir(CONFIG_DIR))
        return false;
    void *scratch = malloc(size);
    if (!scratch) return false;
    bool committed = read_record(f.path, scratch, size);
    bool saved = false;
    if (!committed && !read_record(f.backup, scratch, size) && read_record(f.temp, scratch, size)) {
        // The first save was interrupted before its rename. Preserve its only
        // complete copy before reusing the temporary path.
        if (!discard(f.path) || rename(f.temp, f.path) != 0) goto done;
        committed = true;
    }
    RecordHeader h = {{'A','P','F','1'}, (uint32_t)size, digest(bytes, size)};
    FILE *out = fopen(f.temp, "wb");
    if (!out) goto done;
    bool written = fwrite(&h, 1, sizeof(h), out) == sizeof(h)
                && fwrite(bytes, 1, size, out) == size && fflush(out) == 0
                && fsync(fileno(out)) == 0;
    if (fclose(out) != 0 || !written || !read_record(f.temp, scratch, size)) goto done;
    if (committed) {
        if (!discard(f.backup) || rename(f.path, f.backup) != 0) goto done;
    } else if (!discard(f.path)) goto done;
    saved = rename(f.temp, f.path) == 0;
done:
    free(scratch);
    return saved;
}

bool bindings_load(Bindings *map, const char *game, int actions)
{
    bindings_defaults(map, actions);
    Bindings stored;
    if (!profile_read(game, "map", &stored, sizeof(stored))) return false;
    for (int i = 0; i < BIND_SLOT_COUNT; ++i)
        if (!bindings_allowed((BindAction)stored.action[i], actions)) return false;
    *map = stored;
    return true;
}

bool bindings_save(const Bindings *map, const char *game)
{
    if (!map) return false;
    for (int i = 0; i < BIND_SLOT_COUNT; ++i)
        if (!bindings_allowed((BindAction)map->action[i], 6)) return false;
    return profile_write(game, "map", map, sizeof(*map));
}
