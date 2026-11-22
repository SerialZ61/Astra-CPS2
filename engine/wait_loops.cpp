#include "cyclone.h"
#include "cps.h"
#include <stdint.h>

extern "C" {
extern void (*AstraCycloneJumpTable[])(void);
void AstraCycloneDbra(), AstraCycloneBeq(), AstraTaskBranch(), Astra1944Branch();
const uint16_t *astraWaitPc;
}

namespace {
bool alpha;
unsigned taskTableEnd, wakeOffset;
const uint16_t alphaScan[] = {
    0x422d,0x849e,0x41ed,0x8290,0x303c,15,0x46fc,0x2600,0x4a2d,0x849e,0x66ea,
    0x1210,0x0c01,4,0x6414,0x46fc,0x2000,0x41e8,32,0x51c8,0xffe4
};
const uint16_t armoredScan[] = {
    0x422d,0x814c,0x41ed,0x804c,0x700f,0x46fc,0x2600,0x4a2d,0x814c,0x66ec,
    0x0c28,4,0,0x6400,0x004e,0x46fc,0x2000,0x41e8,16,0x51c8,0xffe2
};
const uint16_t wait1944[] = {0x46fc,0x2000,0x4a79,0x0092,0x1cc4,0x6700,0xfff8};

template<size_t N>
bool matchTask(const uint16_t *pc, const uint16_t (&sequence)[N], bool copyState)
{
    const unsigned repeatedWake = copyState ? 9 : 8;
    for (unsigned i = 0; i < N; ++i) {
        if (i == 1 || i == 3 || i == repeatedWake) continue;
        if (pc[i] != sequence[i]) return false;
    }
    if (pc[1] != pc[repeatedWake]) return false;
    const int start = 0x8000 + (int16_t)pc[3]; // A5 must equal FF8000 at runtime.
    const unsigned end = start + (copyState ? 32u : 16u) * 16;
    if (end >= 0x10000) return false;
    wakeOffset = 0x8000 + (int16_t)pc[1];
    taskTableEnd = 0xff0000 + end;
    alpha = copyState;
    astraWaitPc = pc + N - 1;
    return true;
}
}

void astraWaitClose()
{
    if (!astraWaitPc) return;
    AstraCycloneJumpTable[0x51c8] = AstraCycloneDbra;
    AstraCycloneJumpTable[0x6700] = AstraCycloneBeq;
    astraWaitPc = nullptr;
}

void astraWaitOpen()
{
    // Both original and relocated revisions use these task scanners. Only
    // the two RAM displacements may vary; all executed opcodes must match.
    const uint16_t *code = reinterpret_cast<const uint16_t *>(CpsCode);
    const unsigned words = (nCpsCodeLen < 0x8000 ? nCpsCodeLen : 0x8000) / 2;
    for (unsigned i = 0; code && i < words; ++i) {
        const uint16_t *pc = code + i;
        if (*pc == 0x422d && i + sizeof(alphaScan)/2 <= words &&
            (matchTask(pc, alphaScan, true) || matchTask(pc, armoredScan, false))) {
            AstraCycloneJumpTable[0x51c8] = AstraTaskBranch;
            return;
        }
        if (*pc == wait1944[0] && i + sizeof(wait1944)/2 <= words &&
            !memcmp(pc, wait1944, sizeof(wait1944))) {
            astraWaitPc = pc + sizeof(wait1944)/2 - 1;
            AstraCycloneJumpTable[0x6700] = Astra1944Branch;
            return;
        }
    }
}

extern "C" int astraTaskBudget(Cyclone *cpu, int cycles)
{
    // At DBRA, A0 already points at the next job. A complete idle visit
    // starts and ends with SR=0x2000 and costs exactly 94/98 Cyclone cycles.
    const unsigned count = cpu->d[0] & 0xffff;
    const unsigned stride = alpha ? 32 : 16;
    const int cost = alpha ? 94 : 98;
    if (count > 15 || !count || cycles < cost || cpu->irq || cpu->srh != 0x20 ||
        (cpu->a[5] & 0xffffff) != 0xff8000 ||
        (cpu->a[0] & 0xffffff) != taskTableEnd - count * stride || CpsRamFF[wakeOffset ^ 1])
        return cycles;

    for (unsigned i = 0; i < count && cycles >= cost; ++i) {
        const unsigned state = CpsRamFF[(cpu->a[0] & 0xffff) ^ 1];
        if (state >= 4) break;
        cpu->a[0] += stride;
        --cpu->d[0];
        if (alpha) cpu->d[1] = (cpu->d[1] & ~255u) | state;
        cycles -= cost;
    }
    return cycles;
}

extern "C" int astra1944Budget(Cyclone *cpu, int cycles)
{
    // The mapped graphics RAM word has no read side effects. No other device
    // writes to it inside this CPU slice. Leave the partial iteration to Cyclone.
    if (cycles < 26 || cpu->irq || CpsRam90[0x21cc4] || CpsRam90[0x21cc5]) return cycles;
    return cycles % 26; // Taken BEQ.W (10) plus TST.W absolute long (16).
}
