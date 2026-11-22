"""Exercise the linked ARM CPS2 emulator using the user's SFA parent ZIP.

python tests/sfa_gameplay.py out/AstraCPS2.elf Roms/sfa.zip qa/all
python tests/sfa_gameplay.py out/AstraCPS2.elf Roms/sfa.zip qa/alternate --alternate
python tests/sfa_gameplay.py out/AstraCPS2.elf Roms/sfa.zip qa/idle --idle
python tests/sfa_gameplay.py --compare qa/all qa/alternate qa/idle
python tests/sfa_gameplay.py out/AstraCPS2.elf Roms/sfa.zip qa/original --original
python tests/sfa_gameplay.py --compare-cache qa/all qa/original

Install unicorn, pyelftools and Pillow for the host Python interpreter.
"""
import argparse
import array
import hashlib
import json
import struct
import wave
from pathlib import Path
from zipfile import ZipFile

from arm_host import ArmCore, BMP, H, PCM, STR, W, rgb565


FIRST_COIN = 480
FIGHT_FRAME = 1560


def inputs(f):
    buttons = 0
    if FIRST_COIN <= f < 820 and (f - FIRST_COIN) % 100 < 4:
        buttons |= 1
    if 510 <= f < 1230 and (f - 510) % 79 < 4:
        buttons |= 2
    if 620 <= f < FIGHT_FRAME and (f - 620) % 53 < 3:
        buttons |= 64
    if f >= FIGHT_FRAME:
        if f % 160 < 104:
            buttons |= 32
        if f % 168 < 6:
            buttons |= 4
        if f % 18 < 3:
            buttons |= 64 << ((f // 18) % 6)
    return buttons


def run(elf, archive, out, alternate, idle, frames, original):
    out.mkdir(parents=True, exist_ok=True)
    core = ArmCore(elf, archive)
    if core.call("cps2_open", STR):
        raise RuntimeError(core.cstr(core.call("cps2_error")))
    print("Opened ZIP with the linked ARM core", flush=True)
    cache_pointer = core.symbols["_ZN12_GLOBAL__N_1L5tilesE"]
    cache = bytes(core.mu.mem_read(cache_pointer, 4))
    if cache == bytes(4):
        raise AssertionError("Color tile cache wasn't allocated, cannot compare both paths")
    if original:
        core.mu.mem_write(cache_pointer, bytes(4))
    address = lambda name: struct.unpack("<I", core.mu.mem_read(core.symbols[name], 4))[0]
    ram = address("CpsRamFF")
    # The user's vintage dump includes an independent XOR table which this
    # emulator doesn't load. Cross-check its reset vectors against the real
    # ARM decrypter up to the physically unused end of the program chip. That
    # last 64 KiB is 0xff in the ROM and 0x00 in the legacy XOR table.
    with ZipFile(archive) as z:
        encrypted, mask = z.read("sfze.03d"), z.read("sfzex.03d")
    expected_code = bytes(a ^ b for a, b in zip(encrypted, mask))
    code = bytes(core.mu.mem_read(address("CpsCode"), len(expected_code)))
    mapped_end = 0x70000
    assert code[:mapped_end] == expected_code[:mapped_end], "Decrypted program differs from XOR reference"
    assert encrypted[mapped_end:] == bytes([255]) * 65536 and mask[mapped_end:] == bytes(65536)
    ports = [core.symbols["CpsInp001"] + 4, core.symbols["CpsInp011"]]
    pcm_hash, ram_hash, shared_video, video_hash = (hashlib.sha256() for _ in range(4))
    captures = {}
    pressed = set()
    audible = [0, 0]
    peaks = [0, 0]
    different_channels = pairs_total = draws = 0
    with wave.open(str(out / "combat.wav"), "wb") as wav:
        wav.setparams((2, 2, 22050, 0, "NONE", "PCM"))
        for frame in range(frames):
            buttons = 0 if idle else inputs(frame)
            draw = not alternate or frame % 2 == 0
            pairs = core.call("cps2_frame", buttons, BMP if draw else 0, PCM)
            if not 0 < pairs <= 370:
                raise RuntimeError(f"Invalid PCM length {pairs} at frame {frame}")
            data = bytes(core.mu.mem_read(PCM, pairs * 4))
            pairs_total += pairs
            pcm_hash.update(data)
            ram_hash.update(core.mu.mem_read(ram, 65536))
            if frame >= FIGHT_FRAME:
                wav.writeframesraw(data)
                samples = array.array("h", data)
                for side in range(2):
                    peak = max(abs(v) for v in samples[side::2])
                    audible[side] += bool(peak)
                    peaks[side] = max(peaks[side], peak)
                different_channels += samples[::2] != samples[1::2]
            actual = bytes(core.mu.mem_read(ports[0], 3) + core.mu.mem_read(ports[1], 3))
            expected = bytes((buttons >> (6 + i)) & 1 for i in range(6))
            if actual != expected:
                raise AssertionError(f"Action ports differ at frame {frame}: {actual} vs {expected}")
            pressed.update(i + 1 for i, value in enumerate(actual) if value)
            if draw:
                draws += 1
                image = core.mu.mem_read(BMP, W * H * 2)
                video_hash.update(image)
                if frame % 2 == 0:
                    shared_video.update(image)
                    if frame % 120 == 0 or frame == frames - 2:
                        captures[frame] = hashlib.sha256(image).hexdigest()
                        rgb565(image).save(out / f"frame-{frame:04}.png")
                        print(f"Captured {frame}", flush=True)
    if original:
        core.mu.mem_write(cache_pointer, cache)
    core.call("cps2_close")
    expected_pairs = frames * 22050 * 100 // 5963
    if pairs_total != expected_pairs:
        raise AssertionError(f"Timing: {pairs_total} vs {expected_pairs}")
    if not idle and (pressed != set(range(1, 7)) or min(audible) == 0 or different_channels == 0):
        raise AssertionError(f"Actions/audio: {pressed}, {audible}, {different_channels}")
    result = dict(elf_sha256=core.elf_hash, zip_sha256=hashlib.sha256(archive.read_bytes()).hexdigest(),
                  frames=frames, rendered=draws, pairs=pairs_total, controls="idle" if idle else "coin/start/attack/walk",
                  actions_seen=sorted(pressed), pcm_sha256=pcm_hash.hexdigest(), ram_sha256=ram_hash.hexdigest(),
                  even_video_sha256=shared_video.hexdigest(), captures=captures, samples_rate=22050,
                  audio_segment_first_frame=FIGHT_FRAME, audible_frames=audible, stereo_distinct_frames=different_channels,
                  peaks=peaks, host_instrumented_heap_peak=core.peak_live, cache_disabled=original,
                  video_sha256=video_hash.hexdigest(),
                  decrypted_program_matches_xor_bytes=mapped_end, remaining_ff_padding_bytes=65536)
    (out / "report.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")


def compare(paths):
    full, half, idle = [json.loads((path / "report.json").read_text()) for path in paths]
    assert full["controls"] == half["controls"] and idle["controls"] == "idle"
    assert half["rendered"] < full["rendered"]
    for key in ("elf_sha256", "zip_sha256", "frames", "pairs"):
        assert full[key] == half[key] == idle[key], key
    for key in ("pcm_sha256", "ram_sha256", "even_video_sha256", "actions_seen"):
        assert full[key] == half[key], key
    differing = [int(k) for k, v in full["captures"].items() if idle["captures"][k] != v]
    assert differing and min(differing) >= FIRST_COIN
    assert any(f >= FIGHT_FRAME for f in differing)
    print(f"{full['frames']} logic frames, {half['rendered']} alternate images, matching video/PCM/RAM.")
    print("Controlled scene differs from idle from capture", min(differing))


def compare_cache(paths):
    optimized, original = [json.loads((path / "report.json").read_text()) for path in paths]
    assert not optimized["cache_disabled"] and original["cache_disabled"]
    for key in ("elf_sha256", "zip_sha256", "frames", "pairs", "rendered", "controls", "video_sha256",
                "pcm_sha256", "ram_sha256", "actions_seen"):
        assert optimized[key] == original[key], key
    print(f"{optimized['frames']} frames, all rendered images, all stereo samples and work RAM match the original renderer.")


if __name__ == "__main__":
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("paths", nargs="+", type=Path)
    p.add_argument("--alternate", action="store_true")
    p.add_argument("--idle", action="store_true")
    p.add_argument("--compare", action="store_true")
    p.add_argument("--original", action="store_true")
    p.add_argument("--compare-cache", action="store_true")
    p.add_argument("--frames", type=int, default=2400)
    args = p.parse_args()
    if args.compare:
        compare(args.paths)
    elif args.compare_cache:
        compare_cache(args.paths)
    else:
        run(*args.paths, args.alternate, args.idle, args.frames, args.original)
