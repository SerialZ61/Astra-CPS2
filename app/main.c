#include "astra_text.h"
#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "cps2.h"
#include "settings.h"
#include "display.h"
#include "library.h"
#include "measurements.h"
#include "menu.h"
#include "pacing.h"
#include "sound.h"

static int16_t pcm[CPS2_MAX_SAMPLES * 2];
static const char *const modes[] = { "Auto", "30 i/s", "Toutes" };
#ifdef ASTRA_ENGLISH
static const char *const screen_modes[] = { "Auto", "30 fps", "All" };
#else
#define screen_modes modes
#endif
static bool native;
static bool continuous;
static enum cabinet_view view, preferred_portrait = VIEW_PORTRAIT;
static enum video_mode mode = VIDEO_AUTO;
static volatile bool clock_reset;

// Capture at most a minute in RAM; the only SD write is after the last frame.
enum { PROFILE_WINDOWS = 60 };
static struct {
    ProfileWindow rows[PROFILE_WINDOWS];
    bool active, audio, continuous;
    unsigned index, empty_base, full_base;
    uint32_t screen_base;
    uint64_t window_start, next_sample, capture_end;
    const char *archive, *cadence;
    int game;
} trace;
static const char *trace_message;

static void show_trace(void)
{
    const char *label = trace.active ? TXT_PROFILE_ACTIVE :
        trace_message ? trace_message : TXT_PROFILE_START;
    printf("\x1b[14;1H%-39.39s", label);
}

static void trace_start(const char *path, int game, bool audio)
{
    memset(&trace, 0, sizeof(trace));
    trace.archive = library_filename(path);
    trace.cadence = modes[mode];
    trace.game = game;
    trace.continuous = continuous;
    trace.audio = audio;
    trace.screen_base = display_submissions();
    trace.empty_base = sound_underruns();
    trace.full_base = sound_drops();
    trace.active = true;
    cps2_set_draw_profiling(true);
    show_trace();
    display_flush_console();
    trace.window_start = svcGetSystemTick();
    trace.next_sample = trace.window_start + SYSCLOCK_ARM11;
    trace.capture_end = trace.window_start + (uint64_t)PROFILE_WINDOWS * SYSCLOCK_ARM11;
}

static bool trace_stop(void)
{
    if (!trace.active) return true;
    trace.active = false;
    cps2_set_draw_profiling(false);
    unsigned count = trace.index;
    if (count < PROFILE_WINDOWS && trace.rows[count].frames) ++count;
    bool saved = !count || profile_append_capture(trace.rows, count, SYSCLOCK_ARM11, trace.archive,
        trace.game, trace.cadence, trace.audio, trace.continuous, display_is_accelerated());
    trace_message = saved ? TXT_PROFILE_DONE : TXT_PROFILE_ERROR;
    show_trace();
    display_flush_console();
    return saved;
}

static void note_status(const char *message)
{
    printf(TXT_LOG_LINE, message);
}

static void apt_event(APT_HookType event, void *unused)
{
    (void)unused;
    if (event == APTHOOK_ONRESTORE || event == APTHOOK_ONWAKEUP) clock_reset = true;
}

static void status_layout(int game, const Bindings *bindings)
{
    printf("\x1b[2J\x1b[1;1H\x1b[1;36mASTRA CPS2\x1b[0m  /  OLD 3DS   v0.6\n");
    printf("%.38s\n\n", cps2_game_title(game));
    for (int i = 0; i < 6; i += 2) {
        printf("%-2s %-15.15s  %-2s %.15s\n",
               bindings_key_name(i), bindings_action_name(bindings->action[i], game),
               bindings_key_name(i+1), bindings_action_name(bindings->action[i+1], game));
    }
    printf("START  %.13s   SELECT  %.12s\n",
           bindings_action_name(bindings->action[6], game),
           bindings_action_name(bindings->action[7], game));
    printf(TXT_GAME_SHORTCUTS);
}

static void show_mode(bool paused, bool audio)
{
    printf(TXT_RATE_VIEW, screen_modes[mode], view == VIEW_PORTRAIT ? "Portrait" : view == VIEW_DPAD_TOP ? TXT_DPAD_UP : view == VIEW_DPAD_BOTTOM ? TXT_DPAD_DOWN : native ? "384 x 224" : "4:3 arcade");
    printf(TXT_GAME_STATUS, paused ? TXT_PAUSED : TXT_PLAYING,
           display_is_accelerated() ? "GPU" : "CPU", audio ? "QSound / DSP" : TXT_NO_DSP);
    printf("\x1b[24;1H%-39s", audio ?
           (continuous ? TXT_CONTINUOUS : TXT_ARCADE_AUDIO) : "");
    show_trace();
    note_status(TXT_LOG_HINT);
    printf("\x1b[28;1H\x1b[1;36m%-8s%-8s%-8s%-8s%s\x1b[0m",
           paused ? TXT_RESUME_BUTTON : " PAUSE", TXT_RATE_BUTTON, TXT_VIEW_BUTTON, TXT_BINDINGS_BUTTON, TXT_GAMES_BUTTON);
    display_flush_console();
}

enum touch_action { TOUCH_NONE, TOUCH_PAUSE, TOUCH_RATE, TOUCH_FORMAT, TOUCH_SETTINGS, TOUCH_GAMES, TOUCH_AUDIO, TOUCH_NOTE, TOUCH_PROFILE };

static enum touch_action touch_control(u32 down)
{
    if (!(down & KEY_TOUCH)) return TOUCH_NONE;
    touchPosition tap;
    hidTouchRead(&tap);
    if (tap.py >= 104 && tap.py < 120) return TOUCH_PROFILE;
    if (tap.py >= 180 && tap.py < 200) return TOUCH_AUDIO;
    if (tap.py >= 200 && tap.py < 216) return TOUCH_NOTE;
    return tap.py >= 216 ? (enum touch_action)(TOUCH_PAUSE + tap.px / 64) : TOUCH_NONE;
}

// True returns to the ROM list. False exits to the Homebrew Launcher.
static bool play_game(const char *path, bool audio)
{
    trace_message = NULL;
    int game = cps2_current_game();
    view = cps2_game_vertical(game) ? preferred_portrait : VIEW_HORIZONTAL;
    display_set_view(native, view);
    Bindings bindings;
    bindings_load(&bindings, cps2_game_id(game), cps2_game_buttons(game));
    bool paused = false, has_picture = false;
    unsigned measured_frames = 0, measured_draws = 0;
    uint32_t screen_start = display_submissions();
    unsigned underruns = sound_underruns(), drops = sound_drops();
    unsigned window_empty = underruns, window_full = drops;
    Measurement latest = {0};
    const u64 ticks_per_frame = (u64)SYSCLOCK_ARM11 * CPS2_FPS_DEN / CPS2_FPS_NUM;
    u64 deadline, window_start, drawn_ticks = 0, plain_ticks = 0;
    char last_stats[320] = TXT_MEASURING;
    FramePacer pacer;
    pacing_reset(&pacer, ticks_per_frame);
    status_layout(game, &bindings);
    printf("\x1b[16;1H%s", last_stats);
    show_mode(paused, audio);
    clock_reset = false;
    deadline = window_start = svcGetSystemTick();

    while (aptMainLoop()) {
        uint64_t video_ticks = 0;
        uint64_t section_start = trace.active ? svcGetSystemTick() : 0;
        display_service();
        if (trace.active) video_ticks = svcGetSystemTick() - section_start;
        hidScanInput();
        u32 held = hidKeysHeld(), down = hidKeysDown();
        const u32 exit_chord = KEY_L | KEY_R | KEY_START;
        const u32 menu_chord = KEY_SELECT | KEY_START;
        enum touch_action tap = touch_control(down);
        if ((held & exit_chord) == exit_chord) return false;
        if ((held & menu_chord) == menu_chord || tap == TOUCH_GAMES) return true;
        bool change_rate = tap == TOUCH_RATE || bindings_pressed(&bindings, BIND_RATE, down);
        bool change_format = tap == TOUCH_FORMAT || bindings_pressed(&bindings, BIND_FORMAT, down);
        bool change_pause = tap == TOUCH_PAUSE || bindings_pressed(&bindings, BIND_PAUSE, down);
        if (trace.active && (clock_reset || change_rate || change_format || change_pause ||
                tap == TOUCH_SETTINGS || tap == TOUCH_NOTE || (tap == TOUCH_AUDIO && audio))) {
            trace_stop();
            clock_reset = true;
        }
        if (tap == TOUCH_PROFILE) {
            if (trace.active) { trace_stop(); clock_reset = true; }
            else if (!paused) trace_start(path, game, audio);
            else {
                trace_message = TXT_PROFILE_RESUME;
                show_trace();
                display_flush_console();
            }
        }
        if (tap == TOUCH_NOTE) {
            if (latest.seconds <= 0) note_status(TXT_WAIT_READING);
            else {
                sound_reset();
                bool saved = measurement_append(&latest, library_filename(path), game,
                                                modes[mode], audio, continuous);
                if (saved) latest = (Measurement){0};
                note_status(saved ? TXT_READING_SAVED : TXT_READING_FAILED);
                clock_reset = true;
            }
            display_flush_console();
        }
        if (tap == TOUCH_AUDIO && audio) {
            continuous = !continuous;
            latest = (Measurement){0};
            clock_reset = true;
            underruns = sound_underruns();
            drops = sound_drops();
            strcpy(last_stats, TXT_MEASURING);
            status_layout(game, &bindings);
            printf("\x1b[16;1H%s", last_stats);
            show_mode(paused, audio);
        }

        if (tap == TOUCH_SETTINGS) {
            sound_reset();
            settings_edit(game, &bindings);
            clock_reset = true;
            status_layout(game, &bindings);
            printf("\x1b[16;1H%s", last_stats);
            show_mode(paused, audio);
            continue;
        }
        if (change_rate) {
            mode = (mode + 1) % VIDEO_MODE_COUNT;
            latest = (Measurement){0};
            pacing_reset(&pacer, ticks_per_frame);
            clock_reset = true;
            underruns = sound_underruns();
            drops = sound_drops();
            strcpy(last_stats, TXT_MEASURING);
            status_layout(game, &bindings);
            printf("\x1b[16;1H%s", last_stats);
            show_mode(paused, audio);
        }
        if (change_format) {
            if (view == VIEW_HORIZONTAL) native = !native;
            else {
                preferred_portrait = view == VIEW_DPAD_BOTTOM ? VIEW_PORTRAIT : view+1;
                view = preferred_portrait;
            }
            display_set_view(native, view);
            if (paused && has_picture) display_redraw();
            show_mode(paused, audio);
        }
        if (change_pause) {
            paused = !paused;
            clock_reset = true;
            show_mode(paused, audio);
        }
        if (clock_reset) {
            clock_reset = false;
            sound_reset();
            deadline = window_start = svcGetSystemTick();
            screen_start = display_submissions();
            measured_frames = measured_draws = 0;
            drawn_ticks = plain_ticks = 0;
            window_empty = sound_underruns();
            window_full = sound_drops();
        }
        if (paused) {
            gspWaitForVBlank();
            continue;
        }

        uint64_t audio_start = trace.active ? svcGetSystemTick() : 0;
        if (audio) sound_wait_for_slot();
        u64 now = svcGetSystemTick();
        uint16_t *pixels = pacing_wants_draw(&pacer, mode, now) ? display_acquire() : NULL;
        uint64_t core_start = trace.active ? svcGetSystemTick() : 0;
        int pairs = cps2_frame(display_directions(bindings_buttons(&bindings, held), view), pixels, pcm);
        uint64_t core_end = trace.active ? svcGetSystemTick() : 0;
        if (pairs < 0) {
            sound_reset();
            menu_error(path, cps2_error());
            return true;
        }
        if (audio) sound_submit(pcm, (unsigned)pairs, continuous);
        uint64_t audio_end = trace.active ? svcGetSystemTick() : 0;
        if (pixels) {
            display_present(pixels);
            has_picture = true;
            ++measured_draws;
        }
        uint64_t submit_end = svcGetSystemTick();
        uint64_t audio_wait = now - audio_start;
        uint32_t elapsed = (uint32_t)(submit_end - now);
        if (trace.active) video_ticks += (core_start - now) + (submit_end - audio_end);
        pacing_record(&pacer, pixels != NULL, elapsed);
        if (pixels) drawn_ticks += elapsed;
        else plain_ticks += elapsed;
        ++measured_frames;
        deadline += ticks_per_frame;
        now = svcGetSystemTick();
        if (now - window_start >= 2 * (u64)SYSCLOCK_ARM11) {
            float seconds = (float)(now - window_start) / SYSCLOCK_ARM11;
            float rate = measured_frames / seconds;
            const float tick_ms = 1000.0f / SYSCLOCK_ARM11;
            uint32_t screen_now = display_submissions();
            unsigned empty = sound_underruns(), full = sound_drops();
            latest = (Measurement){ seconds, rate, (screen_now - screen_start) / seconds,
                                    empty - window_empty, full - window_full };
            window_empty = empty;
            window_full = full;
            unsigned plain_frames = measured_frames - measured_draws;
            char sound_stats[64] = "";
            if (audio) snprintf(sound_stats, sizeof(sound_stats), TXT_AUDIO_COUNTS,
                                empty - underruns, full - drops);
            snprintf(last_stats, sizeof(last_stats),
                     TXT_GAME_SPEED
                     TXT_DISPLAY_RATE
                     TXT_DRAW_TIME,
                     rate * 100 * CPS2_FPS_DEN / CPS2_FPS_NUM, rate,
                     (screen_now - screen_start) / seconds, measured_draws / seconds,
                     measured_draws ? drawn_ticks * tick_ms / measured_draws : 0.0f,
                     plain_frames ? plain_ticks * tick_ms / plain_frames : 0.0f, sound_stats);
            printf("\x1b[16;1H%s", last_stats);
            display_flush_console();
            screen_start = screen_now;
            window_start = now;
            measured_frames = measured_draws = 0;
            drawn_ticks = plain_ticks = 0;
        }
        now = svcGetSystemTick();
        if (now < deadline) {
            if (audio && sound_needs_refill()) {
                u64 slack = deadline - now;
                u64 advance = ticks_per_frame / 8;
                deadline -= slack < advance ? slack : advance;
            }
            display_wait_until(deadline);
        }
        else if (now - deadline > 2 * ticks_per_frame) deadline = now;
        if (trace.active && !clock_reset) {
            uint64_t end = svcGetSystemTick();
            ProfileWindow *w = &trace.rows[trace.index];
            w->duration = end - trace.window_start;
            ++w->frames;
            w->drawn += pixels != NULL;
            w->submitted = display_submissions() - trace.screen_base;
            w->empty = sound_underruns() - trace.empty_base;
            w->full = sound_drops() - trace.full_base;
            uint64_t core = core_end - core_start;
            w->core_ticks += core;
            if (core > w->max_core_ticks) w->max_core_ticks = core;
            w->draw_ticks += cps2_draw_ticks();
            w->video_ticks += video_ticks;
            w->sound_ticks += audio_end - core_end;
            w->audio_wait_ticks += audio_wait;
            w->wait_ticks += end - now;
            if (end >= trace.next_sample) {
                // Keep boundaries on the capture clock even when a long frame straddles a second.
                // A frame spanning more than one second stays in one measured window.
                trace.next_sample += (1 + (end - trace.next_sample) / SYSCLOCK_ARM11) * SYSCLOCK_ARM11;
                ++trace.index;
                trace.screen_base += w->submitted;
                trace.empty_base += w->empty;
                trace.full_base += w->full;
                trace.window_start = end;
                if (end >= trace.capture_end || trace.index == PROFILE_WINDOWS) {
                    trace_stop();
                    clock_reset = true;
                }
            }
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    display_init();
    RomLibrary library = {0};
    library_scan(&library);
    int selected = library.count == 1 ? 0 : -1;
    const char *external = argc > 1 ? argv[1] : NULL;
    const char *ext = external ? strrchr(external, '.') : NULL;
    if (!ext || strcasecmp(ext, ".zip")) external = NULL;
    int last = 0;
    bool sound_tried = false, audio = false;
    aptHookCookie hook;
    aptHook(&hook, apt_event, NULL);
    while (aptMainLoop()) {
        const char *path;
        if (external) {
            path = external;
            external = NULL;
        } else {
            if (selected < 0) selected = menu_choose(&library, last);
            if (selected < 0) break;
            path = library.entries[selected].path;
            last = selected;
            selected = -1;
        }
        printf(TXT_LOADING_SCREEN, library_filename(path));
        display_flush_console();
        if (cps2_open(path) != 0) {
            record_load_error(library_filename(path), cps2_error());
            menu_error(path, cps2_error());
            selected = -1;
            continue;
        }
        if (!sound_tried) {
            audio = sound_open();
            sound_tried = true;
        }
        bool again = play_game(path, audio);
        sound_reset();
        if (!trace_stop() && again) menu_error(path, TXT_PROFILE_WRITE_FAILED);
        cps2_close();
        if (!again) break;
        selected = -1;
    }
    aptUnhook(&hook);
    sound_close();
    library_free(&library);
    display_exit();
    gfxExit();
    return 0;
}
