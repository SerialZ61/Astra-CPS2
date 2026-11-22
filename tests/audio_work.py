"""Replay a credited game and count ARM block instructions inside the sound CPU, mixer and draw calls."""
import argparse
import hashlib
import json
from collections import Counter
from pathlib import Path

from unicorn import UC_HOOK_BLOCK, UC_HOOK_CODE
from unicorn.arm_const import UC_ARM_REG_LR

from arm_host import ArmCore, STR, BMP, PCM, W, H, rgb565
from sfa_gameplay import inputs


def replay(elf, archive, output, dispatch_offset, no_bomb, capture):
    core = ArmCore(elf, archive)
    assert core.call("cps2_open", STR) == 0, core.cstr(core.call("cps2_error"))
    mu = core.mu
    symbols = core.symbols
    def value(address, size=4):
        return int.from_bytes(mu.mem_read(address, size), "little")
    zones = {symbols[name]: group for name, group in [
        ("_Z10Z80Executei", "z80"), ("_Z9QscUpdatei", "mix"), ("_Z7CpsDrawv", "draw")
    ]}
    # Keep the comparison independent of relocated host pointers.
    z80 = symbols["_ZL3Z80"]
    work = value(symbols["CpsRamFF"])
    gfx = value(symbols["CpsRam90"])
    shared = [value(symbols[s]) for s in ("CpsZRamC0", "CpsZRamF0")]
    rom = value(symbols["CpsZRom"])
    hashes = {key: hashlib.sha256() for key in ("pixels", "stereo", "memory", "z80")}
    probes = {1350, 1351, 1710, 1711, 1718, 1719, 1920, 1921}
    samples = []
    pc_counts = Counter()
    bomb = archive.stem == "1944"
    for frame in range(2000):
        draw = frame % 2 == 0
        if frame in probes:
            stack = []
            cost = Counter()
            def count(emu, addr, size, _):
                while stack and stack[-1][0] == addr:
                    stack.pop()
                if addr in zones:
                    stack.append((emu.reg_read(UC_ARM_REG_LR), zones[addr]))
                cost[stack[-1][1] if stack else "other"] += size // 4
            mu.ctl_flush_tb()
            hook = mu.hook_add(UC_HOOK_BLOCK, count)
            if dispatch_offset and frame == 1710:
                dispatch = symbols["_Z10Z80Executei"] + dispatch_offset
                trace = mu.hook_add(UC_HOOK_CODE, lambda *args: pc_counts.update([value(z80 + 4, 2)]),
                                    begin=dispatch, end=dispatch)
        keys = inputs(frame)
        if bomb and frame >= 1560:
            keys = (64 if frame % 8 < 4 else 0) | (128 if not no_bomb and 1710 <= frame < 1714 else 0)
        pairs = core.call("cps2_frame", keys, BMP if draw else 0, PCM)
        assert pairs in (369, 370)
        if frame in probes:
            if dispatch_offset and frame == 1710:
                mu.hook_del(trace)
            mu.hook_del(hook)
            mu.ctl_flush_tb()
            assert not stack
            samples.append(dict(frame=frame, draw=draw, costs=dict(cost)))
        if draw:
            pixels = mu.mem_read(BMP, W * H * 2)
            hashes["pixels"].update(pixels)
            if capture and frame in (1708, 1718, 1732, 1754):
                capture.mkdir(parents=True, exist_ok=True)
                rgb565(pixels).save(capture / f"{frame}.png")
        hashes["stereo"].update(mu.mem_read(PCM, pairs * 4))
        hashes["z80"].update(mu.mem_read(z80, 63))
        for addr, size in [(work, 65536), (gfx, 0x30000), *((s, 4096) for s in shared)]:
            hashes["memory"].update(mu.mem_read(addr, size))
    sites = [[hex(pc), count, bytes(mu.mem_read(rom + pc, 24)).hex()] for pc, count in pc_counts.most_common(30) if pc < 0x8000]
    core.call("cps2_close")
    result = dict(elf=core.elf_hash, game=archive.stem, hashes={k:h.hexdigest() for k,h in hashes.items()},
                  samples=samples, sites=sites)
    output.write_text(json.dumps(result, indent=2))


if __name__ == "__main__":
    p = argparse.ArgumentParser(description=__doc__)
    for arg in ("elf", "archive", "output"):
        p.add_argument(arg, type=Path)
    p.add_argument("--dispatch-offset", type=lambda x:int(x, 0), default=0)
    p.add_argument("--no-bomb", action="store_true")
    p.add_argument("--capture", type=Path)
    args = p.parse_args()
    replay(args.elf, args.archive, args.output, args.dispatch_offset, args.no_bomb, args.capture)
