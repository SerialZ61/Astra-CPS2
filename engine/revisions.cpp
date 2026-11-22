#include "burnint.h"

// A revision uses its family's input wiring, draw, reset and lifecycle
// callbacks. Only its physical ROM inventory and board differences vary.
#define ASTRA_REVISION(tag, base, id, title, parent, extraHardware) \
    extern BurnDriver base; BurnDriver tag; STD_ROM_PICK(tag) STD_ROM_FN(tag)
#include "revision_roms.inc"
#undef ASTRA_REVISION

void astraInitRevisions()
{
    static bool ready;
    if (ready) return;
#define ASTRA_REVISION(tag, base, id, title, parent, extraHardware) \
    tag = base; tag.szShortName = id; tag.szFullNameA = title; \
    tag.szFullNameW = nullptr; tag.szParent = parent; \
    tag.flags |= BDF_CLONE; tag.hardware |= extraHardware; \
    tag.GetRomInfo = tag##RomInfo; tag.GetRomName = tag##RomName;
#define ASTRA_REVISION_REGISTRY_ONLY
#include "revision_roms.inc"
#undef ASTRA_REVISION_REGISTRY_ONLY
#undef ASTRA_REVISION
    ready = true;
}
