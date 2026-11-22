#include "library.h"
#include "cps2.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

const char *library_filename(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash ? slash + 1 : path;
}

enum { STEM_CAPACITY = 64 };

static bool archive_stem(const char *path, char stem[STEM_CAPACITY])
{
    const char *file = library_filename(path);
    const char *dot = strrchr(file, '.');
    if (!dot || strcasecmp(dot, ".zip")) return false;
    size_t length = (size_t)(dot - file);
    if (!length || length >= STEM_CAPACITY) return false;
    memcpy(stem, file, length);
    stem[length] = 0;
    return true;
}

int library_game_for_path(const char *path)
{
    char stem[STEM_CAPACITY];
    return archive_stem(path, stem) ? cps2_archive_game(stem) : LIBRARY_UNKNOWN;
}

const char *library_parent_hint(const RomEntry *entry)
{
    if (entry->game < 0) return NULL;
    char stem[STEM_CAPACITY];
    const char *donor = archive_stem(entry->path, stem) ? cps2_archive_parent(stem) : NULL;
    return donor && *donor ? donor : cps2_game_parent(entry->game);
}

bool library_reference_game(int game)
{
    return game >= 0 && !strcmp(cps2_game_id(game), "sfa");
}

static const char *family(int game)
{
    if (game < 0) return "";
    const char *parent = cps2_game_parent(game);
    return parent && *parent ? parent : cps2_game_id(game);
}

static int section(int game)
{
    if (game == LIBRARY_UNMATCHED) return 2;
    if (game < 0) return 3;
    return strcmp(family(game), "sfa") == 0 ? 0 : 1;
}

static bool same_family(const RomLibrary *library, int first, int second)
{
    int a = library->entries[first].game, b = library->entries[second].game;
    if (a < 0 || b < 0) return a == b;
    return strcmp(family(a), family(b)) == 0;
}

int library_next_family(const RomLibrary *library, int selected, int step)
{
    int count = (int)library->count;
    if (selected < 0 || selected >= count) return 0;
    if (step > 0) {
        int next = selected + 1;
        while (next < count && same_family(library, selected, next)) ++next;
        return next == count ? 0 : next;
    }
    while (selected && same_family(library, selected - 1, selected)) --selected;
    int previous = selected ? selected - 1 : count - 1;
    while (previous && same_family(library, previous - 1, previous)) --previous;
    return previous;
}

static bool add_file(RomLibrary *library, const char *dir, const char *name, int game)
{
    // Keep the installation directory first when several frontends share a set.
    for (size_t i = 0; i < library->count; ++i) {
        if (!strcasecmp(library_filename(library->entries[i].path), name)) return true;
    }
    if (library->count == library->capacity) {
        size_t capacity = library->capacity ? library->capacity * 2 : 16;
        RomEntry *entries = realloc(library->entries, capacity * sizeof(*entries));
        if (!entries) return false;
        library->entries = entries;
        library->capacity = capacity;
    }
    size_t dirlen = strlen(dir), namelen = strlen(name);
    char *path = malloc(dirlen + namelen + 2);
    if (!path) return false;
    memcpy(path, dir, dirlen);
    path[dirlen] = '/';
    memcpy(path + dirlen + 1, name, namelen + 1);
    library->entries[library->count++] = (RomEntry){ path, game };
    return true;
}

static int compare_games(const void *first, const void *second)
{
    const RomEntry *a = first, *b = second;
    int cmp = section(a->game) - section(b->game);
    if (cmp) return cmp;
    if (a->game >= 0) {
        const char *fa = family(a->game), *fb = family(b->game);
        cmp = strcasecmp(fa, fb);
        if (cmp) return cmp;
        bool a_parent = !strcmp(fa, cps2_game_id(a->game));
        bool b_parent = !strcmp(fb, cps2_game_id(b->game));
        if (a_parent != b_parent) return a_parent ? -1 : 1;
        cmp = strcasecmp(cps2_game_title(a->game), cps2_game_title(b->game));
    }
    return cmp ? cmp : strcasecmp(library_filename(a->path), library_filename(b->path));
}

void library_scan(RomLibrary *library)
{
    static const struct { const char *path; bool dedicated; } dirs[] = {
        { "sdmc:/3ds/AstraCPS2/roms", true },
        { "sdmc:/roms/arcade/cps2", false },
        { "sdmc:/roms", false },
        { "sdmc:/roms/arcade/fba2012", false },
    };
    library_free(library);
    for (size_t i = 0; i < sizeof(dirs) / sizeof(*dirs); ++i) {
        DIR *dir = opendir(dirs[i].path);
        if (!dir) continue;
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            const char *name = entry->d_name;
            const char *ext = strrchr(name, '.');
            if (*name == '.' || !ext || strcasecmp(ext, ".zip")) continue;
#ifdef DT_DIR
            if (entry->d_type == DT_DIR) continue;
#endif
            int game = library_game_for_path(name);
            if (game == LIBRARY_UNKNOWN && !dirs[i].dedicated) continue;
            if (!add_file(library, dirs[i].path, name, game)) {
                library->incomplete = true;
                break;
            }
        }
        closedir(dir);
        if (library->incomplete) break;
    }
    if (library->count > 1)
        qsort(library->entries, library->count, sizeof(*library->entries), compare_games);
}

void library_free(RomLibrary *library)
{
    for (size_t i = 0; i < library->count; ++i) free(library->entries[i].path);
    free(library->entries);
    *library = (RomLibrary){0};
}
