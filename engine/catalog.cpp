#include "cps2.h"
#include "burnint.h"
#include <strings.h>

const BurnDriver *astra_driver(int index);

namespace {
struct Game {
    const char *title;
    int buttons;
    int clockMHz;
};
const Game games[] = {
#define ASTRA_GAME(driver, title, buttons, mhz) {title, buttons, mhz},
#include "drivers.inc"
#undef ASTRA_GAME
};
struct ArchiveName { const char *stem, *driver, *donor; };
const ArchiveName archives[] = {
#define ASTRA_ARCHIVE(stem, driver, donor) {stem, driver, donor},
#include "archive_names.inc"
#undef ASTRA_ARCHIVE
    {nullptr, nullptr, nullptr}
};
const ArchiveName *archiveName(const char *stem) {
    for (const ArchiveName *p = archives; p->stem; ++p)
        if (!strcasecmp(stem, p->stem)) return p;
    return nullptr;
}
}

int cps2_game_count() { return sizeof(games) / sizeof(games[0]); }

int cps2_archive_game(const char *stem) {
    if (!stem) return -1;
    const ArchiveName *alias = archiveName(stem);
    const char *id = alias ? alias->driver : stem;
    if (!*id) return -2;
    for (int i = 0; i < cps2_game_count(); ++i)
        if (!strcasecmp(id, cps2_game_id(i))) return i;
    return -1;
}

const char *cps2_archive_parent(const char *stem) {
    const ArchiveName *alias = stem ? archiveName(stem) : nullptr;
    return alias && *alias->donor ? alias->donor : nullptr;
}

const char *cps2_game_id(int game) {
    const BurnDriver *driver = astra_driver(game);
    return driver ? driver->szShortName : nullptr;
}

const char *cps2_game_parent(int game) {
    const BurnDriver *driver = astra_driver(game);
    return driver ? driver->szParent : nullptr;
}

const char *cps2_game_title(int game) {
    return astra_driver(game) ? games[game].title : nullptr;
}

int cps2_game_buttons(int game) { return astra_driver(game) ? games[game].buttons : 0; }

int cps2_game_vertical(int game) {
    const BurnDriver *driver = astra_driver(game);
    return driver && (driver->flags & BDF_ORIENTATION_VERTICAL);
}

int astra_game_clock(int game) { return astra_driver(game) ? games[game].clockMHz * 1000000 : 0; }

bool astra_main_program(int game, unsigned index) {
    const BurnDriver *driver = astra_driver(game);
    BurnRomInfo rom = {};
    return driver && !driver->GetRomInfo(&rom, index) && (rom.nType & 15) == 1;
}

int cps2_game_chip(int game, unsigned index, const char **name, uint32_t *bytes, uint32_t *crc) {
    const BurnDriver *driver = astra_driver(game);
    BurnRomInfo chip = {};
    char *label = nullptr;
    if (!driver || driver->GetRomInfo(&chip, index) || driver->GetRomName(&label, index, 0))
        return 1;
    if (name) *name = label;
    if (bytes) *bytes = chip.nLen;
    if (crc) *crc = chip.nCrc;
    return 0;
}
