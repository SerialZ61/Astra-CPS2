#include "astra_text.h"
#include "romzip.h"
#include "cps2.h"
#include "unzip.h"

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

bool astra_main_program(int game, unsigned index);

namespace {
struct ChipKey {
    uint32_t size, crc;
    bool operator==(const ChipKey &other) const { return size == other.size && crc == other.crc; }
};

struct Archive {
    std::string path;
    std::vector<ChipKey> keys;
    bool readable = false;
    explicit Archive(const std::string &name) : path(name) {
        unzFile zip = unzOpen(path.c_str());
        if (!zip) return;
        int rc = unzGoToFirstFile(zip);
        while (rc == UNZ_OK) {
            unz_file_info file;
            if (unzGetCurrentFileInfo(zip, &file, nullptr, 0, nullptr, 0, nullptr, 0) != UNZ_OK) break;
            keys.push_back({static_cast<uint32_t>(file.uncompressed_size), static_cast<uint32_t>(file.crc)});
            rc = unzGoToNextFile(zip);
        }
        readable = rc == UNZ_END_OF_LIST_OF_FILE;
        unzClose(zip);
    }
    bool has(const ChipKey &key) const {
        return readable && std::find(keys.begin(), keys.end(), key) != keys.end();
    }
};

struct Chip {
    ChipKey key;
    const char *name;
    int source;
};
std::vector<Chip> loaded;
unzFile files[2];
char readError[160];

int archiveIndex(std::vector<Archive> &archives, const std::string &path) {
    for (size_t i = 0; i < archives.size(); ++i)
        if (archives[i].path == path) return static_cast<int>(i);
    archives.emplace_back(path);
    return static_cast<int>(archives.size() - 1);
}

// Try only this revision and its declared parent. At least one matching
// chip must actually come from the selected ZIP and distinguish it from
// the parent; shared graphics alone cannot identify a renamed split set.
bool resolve(std::vector<Archive> &archives, int game, const std::string &folder,
             const char *parent, bool named, char *error, size_t capacity) {
    std::vector<Chip> chips;
    ChipKey key;
    const char *name;
    unsigned present = 0;
    for (unsigned i = 0; !cps2_game_chip(game, i, &name, &key.size, &key.crc); ++i) {
        const bool found = archives[0].has(key);
        chips.push_back({key, name, found ? 0 : -1});
        present += found;
    }
    if (!present || chips.empty()) return false;
    int donor = -1;
    if (present < chips.size() && parent && *parent) {
        donor = archiveIndex(archives, folder + parent + ".zip");
        if (!archives[donor].readable) {
            if (named) std::snprintf(error, capacity,
                TXT_MISSING_PARENT, parent);
            return false;
        }
        bool specific = false;
        for (size_t i = 0; i < chips.size(); ++i) {
            Chip &c = chips[i];
            bool shared = archives[donor].has(c.key);
            if (c.source == 0 && !shared && astra_main_program(game, i)) specific = true;
            else if (c.source < 0 && shared) c.source = 1;
        }
        if (!specific) return false;
    }
    for (const Chip &c : chips) {
        if (c.source >= 0) continue;
        if (named || !*error) {
            std::snprintf(error, capacity, TXT_MISSING_CHIP,
                          cps2_game_id(game), c.name, static_cast<unsigned long>(c.key.crc),
                          parent ? TXT_PARENT : "", parent ? parent : "", parent ? ".zip" : "");
        }
        return false;
    }
    files[0] = unzOpen(archives[0].path.c_str());
    if (donor >= 0) files[1] = unzOpen(archives[donor].path.c_str());
    if (!files[0] || (donor >= 0 && !files[1])) {
        romzip_release();
        std::snprintf(error, capacity, TXT_REOPEN_FAILED);
        return false;
    }
    loaded.swap(chips);
    error[0] = 0;
    return true;
}
}

int romzip_prepare(const char *path, int requested, char *error, size_t capacity) {
    romzip_release();
    readError[0] = 0;
    if (!error || !capacity) return -1;
    error[0] = 0;
    if (!path || requested < -1 || requested >= cps2_game_count()) {
        std::snprintf(error, capacity, TXT_BAD_SELECTION);
        return -1;
    }
    std::vector<Archive> archives;
    archives.emplace_back(path);
    if (!archives[0].readable) {
        std::snprintf(error, capacity, TXT_BAD_DIRECTORY);
        return -1;
    }
    const std::string full(path);
    const size_t sep = full.find_last_of("/\\");
    const std::string folder = full.substr(0, sep == std::string::npos ? 0 : sep + 1);
    std::string stem = full.substr(folder.size());
    const size_t dot = stem.find_last_of('.');
    if (dot != std::string::npos) stem.resize(dot);
    const int named = cps2_archive_game(stem.c_str());
    int first = requested >= 0 ? requested : named;
    if (first >= 0) {
        const char *donor = first == named ? cps2_archive_parent(stem.c_str()) : nullptr;
        if (!donor) donor = cps2_game_parent(first);
        if (resolve(archives, first, folder, donor, true, error, capacity)) return first;
    }
    if (requested < 0) {
        for (int game = 0; game < cps2_game_count(); ++game) {
            if (game != first && resolve(archives, game, folder, cps2_game_parent(game),
                                         false, error, capacity)) return game;
        }
    }
    if (archives[0].has({0x80000, 0x824e4a90}) && archives[0].has({0x80000, 0xcac02153})) {
        std::snprintf(error, capacity, TXT_BAD_MARVEL);
        return -1;
    }
    if (archives[0].has({0x400000, 0x2eaa5e10})) {
        std::snprintf(error, capacity, archives[0].has({0x400000, 0x1147406a})
            ? TXT_GIGA_FILLER
            : TXT_GIGA_BOARD);
        return -1;
    }
    if (!error[0]) std::snprintf(error, capacity, TXT_UNSUPPORTED);
    return -1;
}

static int read_chip(unsigned char *destination, int *written, int index, RomChunk consume, void *context) {
    static unsigned char block[16384];
    if (written) *written = 0;
    if ((!destination && !consume) || index < 0 || static_cast<size_t>(index) >= loaded.size()) return 1;
    const Chip &chip = loaded[index];
    unzFile zip = files[chip.source];
    const uint32_t size = chip.key.size;
    for (int rc = unzGoToFirstFile(zip); rc == UNZ_OK; rc = unzGoToNextFile(zip)) {
        unz_file_info file;
        if (unzGetCurrentFileInfo(zip, &file, nullptr, 0, nullptr, 0, nullptr, 0) != UNZ_OK) break;
        if (file.uncompressed_size != size || file.crc != chip.key.crc) continue;
        if ((file.flag & 1) || (file.compression_method == 0 && file.compressed_size != size)) break;
        if (unzOpenCurrentFile(zip) != UNZ_OK) break;
        uint32_t done = 0;
        while (done < size) {
            unsigned count = consume ? std::min<unsigned>(sizeof(block), size - done) : size - done;
            unsigned char *out = consume ? block : destination + done;
            unsigned got = 0;
            while (got < count) {
                int n = unzReadCurrentFile(zip, out + got, count - got);
                if (n <= 0) break;
                got += n;
            }
            if (got != count) break;
            if (consume) consume(context, done, block, got);
            done += got;
        }
        if (unzCloseCurrentFile(zip) != UNZ_OK || done != size) break;
        if (written) *written = static_cast<int>(done);
        return 0;
    }
    std::snprintf(readError, sizeof(readError), TXT_READ_FAILED,
                  chip.name, static_cast<unsigned long>(chip.key.crc));
    return 1;
}

int romzip_load(unsigned char *destination, int *written, int index) {
    return read_chip(destination, written, index, nullptr, nullptr);
}

int romzip_stream(int index, RomChunk consume, void *context) {
    return read_chip(nullptr, nullptr, index, consume, context);
}

const char *romzip_error() { return readError; }

void romzip_release() {
    for (unzFile &file : files) {
        if (file) unzClose(file);
        file = nullptr;
    }
    loaded.clear();
}
