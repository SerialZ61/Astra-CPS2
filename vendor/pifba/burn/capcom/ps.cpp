// PSound (CPS1 sound)
#include "cps.h"
#include "driver.h"
extern "C" {
 #include "ym2151.h"
}

unsigned char PsndCode, PsndFade;						// Sound code/fade sent to the z80 program

static int nSyncPeriod;
static int nSyncNext;

static int nCyclesDone;

static void drvYM2151IRQHandler(int nStatus)
{
	if (nStatus) {
		ZetSetIRQLine(0xFF, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

int PsndInit()
{
	// Final Fight's Z80 and YM2151 share the 3.579545 MHz crystal.
	nCpsZ80Cycles = 3579545 * 100 / nBurnFPS;
	nSyncPeriod = nCpsZ80Cycles / 8 /*/ 32*/;

	// Init PSound z80
	if (PsndZInit()!= 0) {
		return 1;
	}

	// Init PSound mixing (not critical if it fails)
	PsmInit();

	YM2151SetIrqHandler(0, &drvYM2151IRQHandler);

	PsndCode = 0; PsndFade = 0;

	nCyclesDone = 0;

	return 0;
}

int PsndExit()
{
	PsmExit();
	PsndZExit();

	return 0;
}

int PsndScan(int nAction)
{
	if (nAction & ACB_DRIVER_DATA) {
		SCAN_VAR(nCyclesDone); SCAN_VAR(nSyncNext);
		PsndZScan(nAction);							// Scan Z80
		SCAN_VAR(PsndCode); SCAN_VAR(PsndFade);		// Scan sound info
	}
	return 0;
}

void PsndNewFrame()
{
	ZetNewFrame();
	PsmNewFrame();
	nSyncNext = nSyncPeriod;

	ZetIdle(nCyclesDone % nCpsZ80Cycles);
	nCyclesDone = 0;
}

int PsndSyncZ80(int nCycles)
{
	while (nSyncNext < nCycles) {
		PsmUpdate(nSyncNext * nBurnSoundLen / nCpsZ80Cycles);
		ZetRun(nSyncNext - ZetTotalCycles());
		nSyncNext += nSyncPeriod;
	}

	ZetRun(nCycles - ZetTotalCycles());
	if (nCycles == nCpsZ80Cycles) {
		// Carry only the instruction overrun across the frame boundary.
		nCyclesDone = ZetTotalCycles() - nCycles;
	}

	return 0;
}
