#include "measurements.h"
#include "cps2.h"
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define APP_DIR "sdmc:/3ds/AstraCPS2"
static const char header[] =
    "archive;pilote;titre_revision;cadence;son;vitesse_pct;simulation_ips;"
    "affichage_ips;audio_vides_fenetre;audio_pleins_fenetre;duree_s\r\n";

static bool write_field(FILE *f, const char *text)
{
    if (fputc('"', f) == EOF) return false;
    for (const char *p = text; *p; ++p) {
        if (*p == '"' && fputc('"', f) == EOF) return false;
        if (fputc(*p, f) == EOF) return false;
    }
    return fputs("\";", f) >= 0;
}

static void decimal(char *text, size_t size, float value)
{
    snprintf(text, size, "%.2f", value);
    char *point = strchr(text, '.');
    if (point) *point = ',';
}

void record_load_error(const char *archive, const char *reason)
{
    if (mkdir("sdmc:/3ds", 0777) && errno != EEXIST) return;
    if (mkdir(APP_DIR, 0777) && errno != EEXIST) return;
    FILE *f = fopen(APP_DIR "/echecs.csv", "ab");
    if (!f) return;
    long size = fseek(f, 0, SEEK_END) == 0 ? ftell(f) : -1;
    bool ok = size >= 0 && (size || fputs("archive;raison;version\r\n", f) >= 0) &&
              write_field(f, archive) && write_field(f, reason) &&
              fputs("0.6\r\n", f) >= 0 && fflush(f) == 0 && fsync(fileno(f)) == 0;
    if (!ok && size >= 0) {
        fflush(f);
        ftruncate(fileno(f), size);
    }
    fclose(f);
}

bool measurement_append(const Measurement *window, const char *archive, int game,
                        const char *cadence, bool audio, bool continuous)
{
    if (!window || window->seconds <= 0 || !isfinite(window->seconds)) return false;
    if (mkdir("sdmc:/3ds", 0777) && errno != EEXIST) return false;
    if (mkdir(APP_DIR, 0777) && errno != EEXIST) return false;
    FILE *f = fopen(APP_DIR "/mesures.csv", "a+b");
    if (!f) return false;
    bool ok = fseek(f, 0, SEEK_END) == 0;
    long original_size = ok ? ftell(f) : -1;
    ok = original_size >= 0;
    if (ok && original_size == 0) ok = fputs(header, f) >= 0;
    if (ok && original_size > 0) {
        char first[sizeof(header)];
        ok = fseek(f, 0, SEEK_SET) == 0 && fgets(first, sizeof(first), f) &&
             !strcmp(first, header) && fseek(f, 0, SEEK_END) == 0;
    }
    char speed[24], simulation[24], display[24], seconds[24];
    decimal(speed, sizeof(speed), window->game_fps * 100 * CPS2_FPS_DEN / CPS2_FPS_NUM);
    decimal(simulation, sizeof(simulation), window->game_fps);
    decimal(display, sizeof(display), window->displayed_fps);
    decimal(seconds, sizeof(seconds), window->seconds);
    ok = ok && write_field(f, archive) && write_field(f, cps2_game_id(game)) &&
         write_field(f, cps2_game_title(game)) && write_field(f, cadence) &&
         write_field(f, audio ? (continuous ? "Continu" : "Arcade") : "Indisponible") &&
         fprintf(f, "%s;%s;%s;", speed, simulation, display) >= 0;
    if (ok) ok = audio ? fprintf(f, "%u;%u;", window->empty, window->full) >= 0 : fputs(";;", f) >= 0;
    if (ok) ok = fprintf(f, "%s\r\n", seconds) >= 0 && fflush(f) == 0 && fsync(fileno(f)) == 0;
    if (!ok && original_size >= 0) {
        // A failed save must not leave half a record at the end of the journal.
        fflush(f);
        ftruncate(fileno(f), original_size);
    }
    return fclose(f) == 0 && ok;
}

static unsigned milliseconds(uint64_t ticks, uint32_t rate)
{
    return (unsigned)((ticks * 1000 + rate / 2) / rate);
}

bool profile_append_capture(const ProfileWindow *rows, unsigned count, uint32_t tick_rate,
                            const char *archive, int game, const char *cadence,
                            bool audio, bool continuous, bool gpu)
{
    static const char profile_header[] =
        "capture;version;archive;pilote;cadence;son;ecran;fenetre;debut_ms;duree_ms;"
        "vitesse_pct;simulation_ips;affichage_ips;trames;dessinees;soumises;audio_vides;"
        "audio_pleins;coeur_ms;dont_dessin_arcade_ms;sortie_son_ms;attente_son_ms;"
        "appels_video_ms;attente_cadence_et_service_video_ms;max_coeur_trame_ms\r\n";
    if (!count || !tick_rate) return false;
    if (mkdir("sdmc:/3ds", 0777) && errno != EEXIST) return false;
    if (mkdir(APP_DIR, 0777) && errno != EEXIST) return false;
    FILE *f = fopen(APP_DIR "/profil.csv", "a+b");
    if (!f) return false;
    long start = fseek(f, 0, SEEK_END) == 0 ? ftell(f) : -1;
    bool ok = start >= 0;
    if (start > 0) {
        char first[sizeof(profile_header)];
        ok = fseek(f, 0, SEEK_SET) == 0 && fgets(first, sizeof(first), f) &&
             !strcmp(first, profile_header) && fseek(f, 0, SEEK_END) == 0;
    } else if (ok) ok = fputs(profile_header, f) >= 0;
    uint64_t elapsed = 0;
    for (unsigned i = 0; ok && i < count; ++i) {
        const ProfileWindow *r = &rows[i];
        float seconds = (float)r->duration / tick_rate;
        if (seconds <= 0 || !r->frames) { ok = false; break; }
        char speed[24], simulation[24], display[24];
        decimal(speed, sizeof(speed), (r->frames / seconds) * 100 * CPS2_FPS_DEN / CPS2_FPS_NUM);
        decimal(simulation, sizeof(simulation), r->frames / seconds);
        decimal(display, sizeof(display), r->submitted / seconds);
        // The capture's starting file offset identifies it even after a restart.
        ok = fprintf(f, "%ld;0.6;", start) >= 0 && write_field(f, archive) &&
             write_field(f, cps2_game_id(game)) && write_field(f, cadence) &&
             write_field(f, audio ? (continuous ? "Continu" : "Arcade") : "Indisponible") &&
             fprintf(f, "%s;%u;%u;%u;%s;%s;%s;%u;%u;%u;", gpu ? "GPU" : "CPU",
                     i + 1, milliseconds(elapsed,tick_rate), milliseconds(r->duration,tick_rate),
                     speed, simulation, display, r->frames, r->drawn, r->submitted) >= 0;
        if (ok) ok = audio ? fprintf(f, "%u;%u;", r->empty, r->full) >= 0 : fputs(";;", f) >= 0;
        if (ok) ok = fprintf(f, "%u;%u;%u;%u;%u;%u;%u\r\n",
            milliseconds(r->core_ticks,tick_rate), milliseconds(r->draw_ticks,tick_rate),
            milliseconds(r->sound_ticks,tick_rate), milliseconds(r->audio_wait_ticks,tick_rate),
            milliseconds(r->video_ticks,tick_rate), milliseconds(r->wait_ticks,tick_rate),
            milliseconds(r->max_core_ticks,tick_rate)) >= 0;
        elapsed += r->duration;
    }
    if (ok) ok = fflush(f) == 0 && fsync(fileno(f)) == 0;
    if (!ok && start >= 0) {
        fflush(f);
        ftruncate(fileno(f), start);
    }
    return fclose(f) == 0 && ok;
}
