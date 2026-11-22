"""Run the linked ARM program in Unicorn, servicing libc I/O and heap calls on the host. Dependencies: unicorn, pyelftools, Pillow."""
import array
import collections
import hashlib
import io
from pathlib import Path
import struct
import sys

from elftools.elf.elffile import ELFFile
from PIL import Image
from unicorn import Uc, UcError, UC_ARCH_ARM, UC_HOOK_INTR, UC_MODE_ARM
from unicorn import arm_const as arm


W, H = 384, 224
HEAP, HEAP_SIZE = 0x08000000, 56 << 20
SCRATCH, SCRATCH_SIZE = 0x0C000000, 2 << 20
STR, BMP, PCM, DONE = SCRATCH, SCRATCH + 0x1000, SCRATCH + 0x30000, SCRATCH + 0x40000
STACK = SCRATCH + SCRATCH_SIZE - 16
REGS = [arm.UC_ARM_REG_R0, arm.UC_ARM_REG_R1, arm.UC_ARM_REG_R2, arm.UC_ARM_REG_R3]


class ArmCore:
    def __init__(self, filename, archive):
        self.mu = Uc(UC_ARCH_ARM, UC_MODE_ARM)
        self.mu.ctl_set_cpu_model(arm.UC_CPU_ARM_1176)
        self.mu.reg_write(arm.UC_ARM_REG_C1_C0_2, 0x00F00000)
        self.mu.reg_write(arm.UC_ARM_REG_FPEXC, 0x40000000)
        self.mu.mem_map(HEAP, HEAP_SIZE)
        self.mu.mem_map(SCRATCH, SCRATCH_SIZE)
        self.free_blocks = [(HEAP, HEAP_SIZE)]
        self.live = self.peak_live = 0
        self.archive = archive
        self.files = {}
        self.symbols = {}
        self.patches = {}
        self.counts = collections.Counter()
        binary = filename.read_bytes()
        self.elf_hash = hashlib.sha256(binary).hexdigest()
        with io.BytesIO(binary) as f:
            elf = ELFFile(f)
            if elf["e_machine"] != "EM_ARM" or elf.elfclass != 32:
                raise ValueError("Expected a 32-bit ARM ELF")
            segments = [s for s in elf.iter_segments() if s["p_type"] == "PT_LOAD" and s["p_memsz"]]
            start = min(s["p_vaddr"] for s in segments) & ~4095
            end = max(s["p_vaddr"] + s["p_memsz"] for s in segments)
            self.mu.mem_map(start, ((end + 4095) & ~4095) - start)
            for segment in segments:
                if segment["p_filesz"]:
                    self.mu.mem_write(segment["p_vaddr"], segment.data())
            symtab = elf.get_section_by_name(".symtab")
            for sym in symtab.iter_symbols():
                if sym["st_value"]:
                    # Prefer external definitions over file-local symbols.
                    if sym["st_info"]["bind"] == "STB_LOCAL":
                        self.symbols.setdefault(sym.name, sym["st_value"])
                    else:
                        self.symbols[sym.name] = sym["st_value"]
        # Use breakpoints in just these OS-facing routines. No Python callback
        # occurs in the per-opcode inner loop of the emulated arcade machine.
        names = ("malloc calloc realloc free memalign aligned_alloc fopen fopen64 fclose fread "
                 "fseek ftell rewind ferror feof fgetc puts printf fflush __syscall_getreent").split()
        for name in names:
            if name not in self.symbols:
                continue
            address = self.symbols[name]
            if (address & ~1) in self.patches:
                continue
            self.patches[address & ~1] = name
            thunk = bytes.fromhex("00df7047") if address & 1 else bytes.fromhex("000000ef1eff2fe1")
            self.mu.mem_write(address & ~1, thunk)
        self.sizes = {}
        self.mu.hook_add(UC_HOOK_INTR, self.interrupt)
        self.mu.mem_write(STR, archive.name.encode() + b"\0")

    def alloc(self, size, align=16):
        size = max(16, (size + 15) & -16)
        for i, (base, extent) in enumerate(self.free_blocks):
            addr = (base + align - 1) & -align
            if addr + size > base + extent:
                continue
            remainder = [(base, addr - base), (addr + size, base + extent - addr - size)]
            self.free_blocks[i:i + 1] = [(p, n) for p, n in remainder if n]
            self.sizes[addr] = size
            self.live += size
            self.peak_live = max(self.peak_live, self.live)
            return addr
        raise MemoryError(f"ARM heap exhausted: {self.live} allocated, {size} requested")

    def release(self, addr):
        if not addr:
            return
        size = self.sizes.pop(addr)
        self.live -= size
        self.free_blocks.append((addr, size))
        self.free_blocks.sort()
        merged = []
        for base, extent in self.free_blocks:
            if merged and merged[-1][0] + merged[-1][1] == base:
                previous, length = merged.pop()
                merged.append((previous, length + extent))
            else:
                merged.append((base, extent))
        self.free_blocks = merged

    def cstr(self, addr):
        data = bytearray()
        while len(data) < 8192:
            chunk = self.mu.mem_read(addr + len(data), 32)
            cut = chunk.find(b"\0")
            if cut >= 0:
                return (data + chunk[:cut]).decode("utf-8", "replace")
            data.extend(chunk)
        raise ValueError("unterminated ARM string")

    def interrupt(self, mu, number, _):
        pc = mu.reg_read(arm.UC_ARM_REG_PC)
        thumb = mu.reg_read(arm.UC_ARM_REG_CPSR) & 0x20
        name = self.patches.get(pc - (2 if thumb else 4))
        a, b, c, d = mu.reg_read_batch(REGS)
        self.counts[name] += 1
        if name == "malloc":
            ret = self.alloc(a)
        elif name in ("memalign", "aligned_alloc"):
            ret = self.alloc(b, a)
        elif name == "calloc":
            ret = self.alloc(a * b)
            if ret and a and b:
                mu.mem_write(ret, bytes(a * b))
        elif name == "realloc":
            ret = self.alloc(b)
            size = min(self.sizes.get(a, 0), b)
            if size:
                mu.mem_write(ret, bytes(mu.mem_read(a, size)))
            self.release(a)
        elif name == "free":
            self.release(a)
            ret = 0
        elif name in ("fopen", "fopen64"):
            filename, mode = self.cstr(a), self.cstr(b)
            leaf = Path(filename).name
            if Path(leaf).suffix.lower() in (".dat", ".hi", ".nv"):
                # Test with a fresh volatile cabinet: optional score/NVRAM files are absent.
                mu.reg_write(arm.UC_ARM_REG_R0, 0)
                return
            if not leaf.lower().endswith(".zip") or mode not in ("rb", "r"):
                raise ValueError(f"Unexpected file access {filename!r} {mode!r}")
            path = self.archive.parent / leaf
            ret = max(self.files, default=0) + 1 if path.is_file() else 0
            if ret:
                self.files[ret] = io.BytesIO(path.read_bytes())
        elif name == "fread":
            data = self.files[d].read(b * c)
            if data:
                mu.mem_write(a, data)
            ret = len(data) // b if b else 0
        elif name == "fseek":
            offset = b - (1 << 32) if b & (1 << 31) else b
            self.files[a].seek(offset, c)
            ret = 0
        elif name == "ftell":
            ret = self.files[a].tell()
        elif name == "rewind":
            self.files[a].seek(0)
            ret = 0
        elif name == "fclose":
            self.files[a].close()
            ret = 0
        elif name == "fgetc":
            data = self.files[a].read(1)
            ret = data[0] if data else -1
        elif name == "feof":
            ret = int(self.files[a].tell() >= self.files[a].getbuffer().nbytes)
        elif name in ("puts", "printf", "fflush", "ferror"):
            ret = 0
        elif name == "__syscall_getreent":
            ret = self.symbols["_impure_data"]
        else:
            raise RuntimeError(f"Unhandled ARM interrupt {number} at {pc:#x}")
        mu.reg_write(arm.UC_ARM_REG_R0, ret & 0xFFFFFFFF)

    def call(self, name, *args):
        pc = self.symbols[name]
        for reg, value in zip(REGS, args):
            self.mu.reg_write(reg, value)
        extra = args[len(REGS):]
        sp = STACK - ((len(extra) * 4 + 7) & ~7)
        if extra:
            self.mu.mem_write(sp, struct.pack("<" + "I" * len(extra), *extra))
        self.mu.reg_write(arm.UC_ARM_REG_SP, sp)
        self.mu.reg_write(arm.UC_ARM_REG_LR, DONE)
        try:
            # A timeout creates an extra host timer thread for every call in
            # Unicorn. Keep it on the startup path, outside the frame loop.
            self.mu.emu_start(pc, DONE, timeout=120_000_000 if name == "cps2_open" else 0)
        except UcError as exc:
            raise RuntimeError(f"{name} failed at ARM PC {self.mu.reg_read(arm.UC_ARM_REG_PC):#x}") from exc
        if self.mu.reg_read(arm.UC_ARM_REG_PC) != DONE:
            raise TimeoutError(f"{name} did not return")
        return self.mu.reg_read(arm.UC_ARM_REG_R0)


def rgb565(data):
    words = array.array("H")
    words.frombytes(data)
    if sys.byteorder != "little":
        words.byteswap()
    rgb = bytearray()
    for pixel in words:
        rgb.extend(((pixel >> 11) * 255 // 31, (pixel >> 5 & 63) * 255 // 63, (pixel & 31) * 255 // 31))
    return Image.frombytes("RGB", (W, H), bytes(rgb))


