#include "astra_text.h"
#include "cps.h"
#include "romzip.h"

const char *cpsLoadStage;
unsigned cpsLoadBytes;
bool CpsPhoenix;
#ifdef ASTRA_CPS2
// The validated CPS2 set fits in normal 3DS application RAM.
static const bool bBurnUseRomCache = false;
static int BurnCacheBlockSize(int) { return 0; }
static void BurnCacheRead(unsigned char*, int) {}
static void UpperFree(void* ptr) { free(ptr); }
#else
#include "gp2xsdk.h"
#include "cache.h"
#endif
// CPS (general)

unsigned char UpperReserved = 0;
int Cps = 0;							// 1 = CPS1, 2 = CPS2, 3 = CPS Changer
int Cps1Qs = 0;

int nCPS68KClockspeed = 0;
int nCpsCycles = 0;						// 68K Cycles per frame
int	nCpsZ80Cycles;

unsigned char *CpsGfx =NULL; unsigned int nCpsGfxLen =0; // All the graphics
unsigned char *CpsGfxSeg[2] = {NULL};
unsigned char *CpsRom =NULL; unsigned int nCpsRomLen =0; // Program Rom (as in rom)
unsigned char *CpsCode=NULL; unsigned int nCpsCodeLen=0; // Program Rom (decrypted)
unsigned char *CpsZRom=NULL; unsigned int nCpsZRomLen=0; // Z80 Roms
char *CpsQSam=NULL; unsigned int nCpsQSamLen=0;	// QSound Sample Roms
unsigned char *CpsAd  =NULL; unsigned int nCpsAdLen  =0; // ADPCM Data
unsigned char *CpsStar=NULL;
unsigned int nCpsGfxScroll[4]={0,0,0,0}; // Offset to Scroll tiles
unsigned int nCpsGfxMask=0;	  // Address mask

// Separate out the bits of a byte
inline static unsigned int Separate(unsigned int b)
{
	unsigned int a = b;									// 00000000 00000000 00000000 11111111
	a  =((a & 0x000000F0) << 12) | (a & 0x0000000F);	// 00000000 00001111 00000000 00001111
	a = ((a & 0x000C000C) <<  6) | (a & 0x00030003);	// 00000011 00000011 00000011 00000011
	a = ((a & 0x02020202) <<  3) | (a & 0x01010101);	// 00010001 00010001 00010001 00010001

	return a;
}

// Precalculated table of the Separate function
static unsigned int SepTable[256];

static int SepTableCalc()
{
	static int bDone = 0;
	if (bDone) {
		return 0;										// Already done it
	}

	for (int i = 0; i < 256; i++) {
		SepTable[i] = Separate(255 - i);
	}

	bDone = 1;											// done it
	return 0;
}

// Allocate space and load up a rom
static int LoadUp(unsigned char** pRom, int* pnRomLen, int nNum)
{
	unsigned char *Rom;
	struct BurnRomInfo ri;

	ri.nLen = 0;
	BurnDrvGetRomInfo(&ri, nNum);	// Find out how big the rom is
	if (ri.nLen <= 0) {
		return 1;
	}

	// Load the rom
	Rom = (unsigned char*)malloc(ri.nLen);
	if (Rom == NULL) {
		return 1;
	}

	if (BurnLoadRom(Rom,nNum,1)) {
		free(Rom);
		return 1;
	}

	// Success
	*pRom = Rom; *pnRomLen = ri.nLen;
	return 0;
}

// ----------------------------CPS1--------------------------------
// Load 1 rom and interleave in the CPS style:
// rom  : aa bb
// --ba --ba --ba --ba --ba --ba --ba --ba 8 pixels (four bytes)
//                                                  (skip four bytes)

static int CpsLoadOne(unsigned char* Tile, int nNum, int nWord, int nShift)
{
	unsigned char *Rom = NULL; int nRomLen=0;
	unsigned char *pt = NULL, *pr = NULL;
	int i;

	LoadUp(&Rom, &nRomLen, nNum);
	if (Rom == NULL) {
		return 1;
	}

	nRomLen &= ~1;								// make sure even

	for (i = 0, pt = Tile, pr = Rom; i < nRomLen; pt += 8) {
		unsigned int Pix;						// Eight pixels
		unsigned char b;
		b = *pr++; i++; Pix = SepTable[b];
		if (nWord) {
			b = *pr++; i++; Pix |= SepTable[b] << 1;
		}

		Pix <<= nShift;
		*((unsigned int *)pt) |= Pix;
	}

	free(Rom);
	return 0;
}

static int CpsLoadOneHack160(unsigned char *Tile, int nNum, int nWord, int nOffset)
{
	int i = 0;
	unsigned char *Rom1 = NULL, *Rom2 = NULL;
	int nRomLen1 = 0, nRomLen2 = 0;
	unsigned char *pt = NULL, *pr = NULL;

	LoadUp(&Rom1, &nRomLen1, nNum);
	if (Rom1 == NULL) {
		return 1;
	}
	LoadUp(&Rom2, &nRomLen2, nNum + 1);
	if (Rom2 == NULL) {
		return 1;
	}

	for (i = 0, pt = Tile, pr = Rom1 + (0x80000 * nOffset); i < 0x80000; pt += 8) {
		unsigned int Pix;		// Eight pixels
		unsigned char b;
		b = *pr++; i++; Pix = SepTable[b];
		if (nWord) {
			b = *pr++; i++; Pix |= SepTable[b] << 1;
		}

		Pix <<= 0;
		*((unsigned int *)pt) |= Pix;
	}

	for (i = 0, pt = Tile, pr = Rom2 + (0x80000 * nOffset); i < 0x80000; pt += 8) {
		unsigned int Pix;		// Eight pixels
		unsigned char b;
		b = *pr++; i++; Pix = SepTable[b];
		if (nWord) {
			b = *pr++; i++; Pix |= SepTable[b] << 1;
		}

		Pix <<= 2;
		*((unsigned int *)pt) |= Pix;
	}

	free(Rom2);
	free(Rom1);
	return 0;
}

static int CpsLoadOnePang(unsigned char *Tile,int nNum,int nWord,int nShift)
{
	int i=0;
	unsigned char *Rom = NULL; int nRomLen = 0;
	unsigned char *pt = NULL, *pr = NULL;

	LoadUp(&Rom, &nRomLen, nNum);
	if (Rom == NULL) {
		return 1;
	}

	nRomLen &= ~1; // make sure even

	for (i = 0x100000, pt = Tile, pr = Rom + 0x100000; i < nRomLen; pt += 8) {
		unsigned int Pix; // Eight pixels
		unsigned char b;
		b = *pr++; i++; Pix = SepTable[b];
		if (nWord) {
			b = *pr++; i++; Pix |= SepTable[b] << 1;
		}

		Pix <<= nShift;
		*((unsigned int *)pt) |= Pix;
	}

	free(Rom);
	return 0;
}

int CpsLoadTiles(unsigned char* Tile, int nStart)
{
	// left  side of 16x16 tiles
	CpsLoadOne(Tile,     nStart    , 1, 0);
	CpsLoadOne(Tile,     nStart + 1, 1, 2);
	// right side of 16x16 tiles
	CpsLoadOne(Tile + 4, nStart + 2, 1, 0);
	CpsLoadOne(Tile + 4, nStart + 3, 1, 2);
	return 0;
}

int CpsLoadTilesPang(unsigned char* Tile, int nStart)
{
	CpsLoadOne(    Tile,     nStart,     1, 0);
	CpsLoadOne(    Tile,     nStart + 1, 1, 2);
	CpsLoadOnePang(Tile + 4, nStart,     1, 0);
	CpsLoadOnePang(Tile + 4, nStart + 1, 1, 2);

	return 0;
}

int CpsLoadTilesHack160(unsigned char* Tile, int nStart)
{
	CpsLoadOneHack160(Tile + 0 + 0x000000, nStart, 1, 0);
	CpsLoadOneHack160(Tile + 4 + 0x000000, nStart, 1, 1);
	CpsLoadOneHack160(Tile + 0 + 0x200000, nStart, 1, 2);
	CpsLoadOneHack160(Tile + 4 + 0x200000, nStart, 1, 3);
	return 0;
}

int CpsLoadTilesByte(unsigned char* Tile, int nStart)
{
	CpsLoadOne(Tile,     nStart + 0, 0, 0);
	CpsLoadOne(Tile,     nStart + 1, 0, 1);
	CpsLoadOne(Tile,     nStart + 2, 0, 2);
	CpsLoadOne(Tile,     nStart + 3, 0, 3);
	CpsLoadOne(Tile + 4, nStart + 4, 0, 0);
	CpsLoadOne(Tile + 4, nStart + 5, 0, 1);
	CpsLoadOne(Tile + 4, nStart + 6, 0, 2);
	CpsLoadOne(Tile + 4, nStart + 7, 0, 3);
	return 0;
}

int CpsLoadStars(unsigned char* pStar, int nStart)
{
	unsigned char* pTemp[2] = { NULL, NULL};
	int nLen;

	for (int i = 0; i < 2; i++) {
		if (LoadUp(&pTemp[i], &nLen, nStart + (i << 1))) {
			free(pTemp[0]);
			free(pTemp[1]);
		}
	}

	for (int i = 0; i < 0x1000; i++) {
		pStar[i] = pTemp[0][i << 1];
		pStar[0x01000 + i] = pTemp[1][i << 1];
	}

	free(pTemp[0]);
	free(pTemp[1]);

	return 0;
}

// ----------------------------CPS2--------------------------------
// Load 1 rom and interleve in the CPS2 style:
// rom  : aa bb -- -- (4 bytes)
// --ba --ba --ba --ba --ba --ba --ba --ba 8 pixels (four bytes)
//                                                  (skip four bytes)

// memory 000000-100000 are in even word fields of first 080000 section
// memory 100000-200000 are in  odd word fields of first 080000 section
// i = ABCD nnnn nnnn nnnn nnnn n000
// s = 00AB Cnnn nnnn nnnn nnnn nnD0

// Each 512 KiB of interleaved input supplies two 1 MiB halves of the tile bank.
struct TilePlane {
    unsigned char *base;
    unsigned shift;
    bool simm;
};

static void decodeTileBlock(void *context, unsigned offset, const unsigned char *src, unsigned size)
{
    const TilePlane &plane = *static_cast<TilePlane *>(context);
    const unsigned input = plane.simm ? offset * 2 : offset;
    unsigned char *first = plane.base + (input / 0x80000) * 0x200000 + (input % 0x80000) * 2;
    // The 16 KiB reader never crosses a bank boundary. A SIMM holds one
    // byte from each source word, while an ordinary ROM contains both.
    unsigned char *second = first + 0x100000;
    const unsigned step = plane.simm ? 2 : 4;
    for (unsigned i = 0; i < size; i += step, first += 8, second += 8) {
        unsigned low = SepTable[src[i]], high = SepTable[src[i + step / 2]];
        if (!plane.simm) {
            low |= SepTable[src[i + 1]] << 1;
            high |= SepTable[src[i + 3]] << 1;
        }
        *reinterpret_cast<unsigned *>(first) |= low << plane.shift;
        *reinterpret_cast<unsigned *>(second) |= high << plane.shift;
    }
}

static int Cps2LoadOne(unsigned char *tile, int index, int word, int shift)
{
    TilePlane plane = {tile, static_cast<unsigned>(shift), !word};
    if (romzip_stream(index, decodeTileBlock, &plane)) return 1;
    if (word) return 0;
    ++plane.shift;
    return romzip_stream(index + 1, decodeTileBlock, &plane);
}

int Cps2LoadTiles(unsigned char* Tile, int nStart)
{
	// left  side of 16x16 tiles
	if (Cps2LoadOne(Tile,     nStart,     1, 0)) return 1;
	if (Cps2LoadOne(Tile,     nStart + 1, 1, 2)) return 1;
	// right side of 16x16 tiles
	if (Cps2LoadOne(Tile + 4, nStart + 2, 1, 0)) return 1;
	if (Cps2LoadOne(Tile + 4, nStart + 3, 1, 2)) return 1;

	return 0;
}

int Cps2LoadTilesSIM(unsigned char* Tile, int nStart)
{
	if (Cps2LoadOne(Tile,     nStart,     0, 0)) return 1;
	if (Cps2LoadOne(Tile,     nStart + 2, 0, 2)) return 1;
	if (Cps2LoadOne(Tile + 4, nStart + 4, 0, 0)) return 1;
	if (Cps2LoadOne(Tile + 4, nStart + 6, 0, 2)) return 1;

	return 0;
}

// ----------------------------------------------------------------

// The file extension indicates the data contained in a file.
// it consists of 2 numbers optionally followed by a single letter.
// The letter indicates the version. The meaning for the nubmers
// is as follows:
// 01 - 02 : Z80 program
// 03 - 10 : 68K program (filenames ending with x contain the XOR table)
// 11 - 12 : QSound sample data
// 13 - nn : Graphics data

static unsigned int nGfxMaxSize;

static int CpsGetROMs(bool bLoad)
{
	char* pRomName;
	struct BurnRomInfo ri;

	unsigned char* CpsCodeLoad = CpsCode;
	unsigned char* CpsRomLoad = CpsRom;
	unsigned int CpsGfxLoad = 0;
	unsigned char* CpsZRomLoad = CpsZRom;
	unsigned char* CpsQSamLoad = (unsigned char*)CpsQSam;

	int nGfxNum = 0;

	if (bLoad) {
		if (!CpsCodeLoad || !CpsRomLoad || !CpsZRomLoad || !CpsQSamLoad) {
			return 1;
		}
	} else {
		nCpsCodeLen = nCpsRomLen = nCpsGfxLen = nCpsZRomLen = nCpsQSamLen = 0;

		nGfxMaxSize = 0;
		if (BurnDrvGetHardwareCode() & HARDWARE_CAPCOM_CPS2_SIMM) {
			nGfxMaxSize = ~0U;
		}
	}

	for (int i = 0; !BurnDrvGetRomName(&pRomName, i, 0); i++) {

		BurnDrvGetRomInfo(&ri, i);

		// SIMM Graphics ROMs
		if (BurnDrvGetHardwareCode() & HARDWARE_CAPCOM_CPS2_SIMM) {
			if ((ri.nType & BRF_GRA) && (ri.nType & 8)) {
				if (bLoad)
				{
					if (Cps2LoadTilesSIM(CpsGfx+CpsGfxLoad, i)) return 1;
					CpsGfxLoad += ri.nLen * 8;
					i += 7;
				} else {
					nCpsGfxLen += ri.nLen;
				}
				continue;
			}
			// SIMM QSound sample ROMs
			if ((ri.nType & BRF_SND) && ((ri.nType & 15) == 13)) {
				if (bLoad) {
					if (BurnLoadRom(CpsQSamLoad, i, 1)) return 1;
					BurnByteswap(CpsQSamLoad, ri.nLen);
					CpsQSamLoad += ri.nLen;
				} else {
					nCpsQSamLen += ri.nLen;
				}
				continue;
			}
			
			// Different interleave SIMM QSound sample ROMs
			if ((ri.nType & BRF_SND) && ((ri.nType & 15) == 15)) {
				if (bLoad) {
					if (BurnLoadRom(CpsQSamLoad + 1, i + 0, 2)) return 1;
					if (BurnLoadRom(CpsQSamLoad + 0, i + 1, 2)) return 1;
					CpsQSamLoad += 2 * ri.nLen;
					++i;
				} else {
					nCpsQSamLen += ri.nLen;
				}
				continue;
			}
		}

		// 68K program ROMs
		if ((ri.nType & 7) == 1) {
			if (bLoad) {
				if (BurnLoadRom(CpsRomLoad, i, 1)) return 1;
				CpsRomLoad += ri.nLen;
			} else {
				nCpsRomLen += ri.nLen;
			}
			continue;
		}
		// XOR tables
		if ((ri.nType & 7) == 2) {
			if (bLoad) {
				if (BurnLoadRom(CpsCodeLoad, i, 1)) return 1;
				CpsCodeLoad += ri.nLen;
			} else {
				nCpsCodeLen += ri.nLen;
			}
			continue;
		}

		// Z80 program ROMs
		if ((ri.nType & 7) == 4) {
			if (bLoad) {
				if (BurnLoadRom(CpsZRomLoad, i, 1)) return 1;
				CpsZRomLoad += ri.nLen;
			} else {
				nCpsZRomLen += ri.nLen;
			}
			continue;
		}

		// Normal Graphics ROMs
		if (ri.nType & BRF_GRA) {
			if (bLoad) {
				if (UpperReserved != 2) {
					if (Cps2LoadTiles(CpsGfx+CpsGfxLoad, i)) return 1;
				} else
				{
					if (Cps2LoadTiles(GETCPSGFX(CpsGfxLoad), i)) return 1;						
				}
				CpsGfxLoad += (nGfxMaxSize == ~0U ? ri.nLen : nGfxMaxSize) * 4;
				i += 3;
			} else {
				if (ri.nLen > nGfxMaxSize) {
					nGfxMaxSize = ri.nLen;
				}
				if (ri.nLen < nGfxMaxSize) {
					nGfxMaxSize = ~0U;
				}
				nCpsGfxLen += ri.nLen;
				nGfxNum++;
			}
			continue;
		}

		// QSound sample ROMs
		if (ri.nType & BRF_SND) {
			if (bLoad) {
				if (BurnLoadRom(CpsQSamLoad, i, 1)) return 1;
				BurnByteswap(CpsQSamLoad, ri.nLen);
				CpsQSamLoad += ri.nLen;
			} else {
				nCpsQSamLen += ri.nLen;
			}
			continue;
		}
	}

	if (bLoad) {
#if 0
		for (unsigned int i = 0; i < nCpsCodeLen / 4; i++) {
			((unsigned int*)CpsCode)[i] ^= ((unsigned int*)CpsRom)[i];
		}
#endif
		if (CpsPhoenix) {
			// These sets store executable opcodes directly in their program chips.
			CpsCode = CpsRom;
			nCpsCodeLen = nCpsRomLen;
		} else {
            cpsLoadStage = TXT_PREPARE_68000;
            cps2_decrypt_game_data();
        }
		
		if (!nCpsCodeLen) return 1;
	} else {

		if (nGfxMaxSize != ~0U) {
			nCpsGfxLen = nGfxNum * nGfxMaxSize;
		}

#if 1 && defined FBA_DEBUG
		if (!nCpsCodeLen) {
			bprintf(PRINT_IMPORTANT, _T("  - 68K ROM size:\t0x%08X (Decrypted with key)\n"), nCpsRomLen);
		} else {
			bprintf(PRINT_IMPORTANT, _T("  - 68K ROM size:\t0x%08X (XOR table size: 0x%08X)\n"), nCpsRomLen, nCpsCodeLen);
		}
		bprintf(PRINT_IMPORTANT, _T("  - Z80 ROM size:\t0x%08X\n"), nCpsZRomLen);
		bprintf(PRINT_IMPORTANT, _T("  - Graphics data:\t0x%08X\n"), nCpsGfxLen);
		bprintf(PRINT_IMPORTANT, _T("  - QSound data:\t0x%08X\n"), nCpsQSamLen);
#endif

		if (/*!nCpsCodeLen ||*/ !nCpsRomLen || !nCpsGfxLen || !nCpsZRomLen || ! nCpsQSamLen) {
			return 1;
		}
	}

	return 0;
}

// ----------------------------------------------------------------

int CpsInit()
{
	int nMemLen, i;

	BurnSetRefreshRate(59.633333);
#ifdef ASTRA_CPS2
    // PiFBA used reduced clocks on GP2X. Select the actual board timing.
    extern int astra_game_clock(int game);
    nCPS68KClockspeed = astra_game_clock(nBurnDrvSelect);
#endif

	if (!nCPS68KClockspeed) {
		if (!(Cps & 1)) {
			nCPS68KClockspeed = 11800000;
		} else {
			nCPS68KClockspeed = 8000000;
		}
	}
	nCPS68KClockspeed = nCPS68KClockspeed * 100 / nBurnFPS;

	if ( bBurnUseRomCache )
		nCpsCodeLen = BurnCacheBlockSize(2);		

	nMemLen = nCpsGfxLen + nCpsRomLen + nCpsCodeLen + nCpsZRomLen + nCpsQSamLen + nCpsAdLen;

	if (Cps1Qs == 1) {
		nMemLen += nCpsZRomLen * 2;
	}

		// Allocate Gfx, Rom and Z80 Roms
        cpsLoadStage = TXT_GRAPHICS_MEMORY;
        cpsLoadBytes = nCpsGfxLen;
        CpsGfx = (unsigned char*)calloc(1, nCpsGfxLen);
        if (!CpsGfx) return 1;
        cpsLoadStage = TXT_PROGRAM_MEMORY;
        cpsLoadBytes = nMemLen - nCpsGfxLen;
        CpsRom = (unsigned char*)calloc(1, cpsLoadBytes);
        if (!CpsRom) return 1;
		CpsCode = CpsRom + nCpsRomLen;
		if (Cps1Qs == 1) {
			CpsEncZRom = CpsCode + nCpsCodeLen;
			CpsZRom = CpsEncZRom + nCpsZRomLen * 2;
		} else {
			CpsZRom = CpsCode + nCpsCodeLen;
		}
		CpsQSam =(char*)(CpsZRom + nCpsZRomLen);
		CpsAd   =(unsigned char*)(CpsQSam + nCpsQSamLen);
		UpperReserved = 0;

	// Create Gfx addr mask
	for (i = 0; i < 31; i++) {
		if ((1 << i) >= (int)nCpsGfxLen) {
			break;
		}
	}
	nCpsGfxMask = (1 << i) - 1;

	// Offset to Scroll tiles
	if (!(Cps & 1)) {
		nCpsGfxScroll[1] = nCpsGfxScroll[2] = nCpsGfxScroll[3] = 0x800000;
	} else {
		nCpsGfxScroll[1] = nCpsGfxScroll[2] = nCpsGfxScroll[3] = 0;
	}

	if ( bBurnUseRomCache ) {
		BurnCacheRead(CpsRom, 0);
		BurnCacheRead(CpsZRom, 1);
		BurnCacheRead(CpsCode, 2);
		BurnCacheRead((unsigned char*)CpsQSam,3);
		BurnCacheRead(CpsGfxSeg[0],4);
		BurnCacheRead(CpsGfxSeg[1],5);
		BurnCacheRead(CpsAd,6);
	}
	else {
		if (nCpsZRomLen>=5) {
			// 77->cfff and rst 00 in case driver doesn't load
			CpsZRom[0] = 0x3E; CpsZRom[1] = 0x77;
			CpsZRom[2] = 0x32; CpsZRom[3] = 0xFF; CpsZRom[4] = 0xCF;
			CpsZRom[5] = 0xc7;
		}
	}

	// mprot
	CpsMProt[0] = 0x40;
	CpsMProt[1] = 0x42;
	CpsMProt[2] = 0x44;
	CpsMProt[3] = 0x46;

	// Board ID (ffight is the default)
	CpsBID[0] = 0x60;
	CpsBID[1] = 0x00;
	CpsBID[2] = 0x04;

	SepTableCalc();									  // Precalc the separate table

	CpsReset = 0; Cpi01A = Cpi01C = Cpi01E = 0;		  // blank other inputs

	nCpsLcReg = 0x66;								  // Layer controller usually at 0x66
	// Usual bits for layer enable
	CpsLayEn[1] = 2; CpsLayEn[2] = 4; CpsLayEn[3] = 8; CpsLayEn[4] = 0; CpsLayEn[5] = 0;

	return 0;
}

static bool runStarted;

int Cps2Init()
{
	Cps = 2;
	CpsPhoenix = (BurnDrvGetHardwareCode() & HARDWARE_CAPCOM_CPS2_PHOENIX) != 0;

	cpsLoadStage = TXT_CHIP_LIST;
	cpsLoadBytes = 0;
	if (CpsGetROMs(false)) {
		return 1;
	}

	if (CpsInit()) return 1;

	cpsLoadStage = TXT_READ_CHIPS;
	cpsLoadBytes = 0;
	if ( !bBurnUseRomCache )
		if (CpsGetROMs(true)) {
			return 1;
		}

	runStarted = true;
	return CpsRunInit();
}

int CpsExit()
{
	CpsPhoenix = false;
	if (runStarted) {
		CpsRunExit();
		runStarted = false;
	}

	CpsLayEn[1] = CpsLayEn[2] = CpsLayEn[3] = CpsLayEn[4] = CpsLayEn[5] = 0;
	nCpsLcReg = 0;
	nCpsGfxScroll[1] = nCpsGfxScroll[2] = nCpsGfxScroll[3] = 0;
	nCpsGfxMask = 0;

	cps2_free_decrypted_code();
	nCpsCodeLen = nCpsRomLen = nCpsGfxLen = nCpsZRomLen = nCpsQSamLen = nCpsAdLen = 0;
	CpsCode = CpsZRom = CpsAd = CpsStar = NULL;

	switch(UpperReserved)
	{
		case 0:
			free(CpsRom);
			free(CpsGfx);
		break;
		case 1:
		free(CpsRom);
		CpsRom = NULL;
		UpperFree(CpsGfx);
		break;
		case 2:
		free(CpsRom);
		CpsRom = NULL;
		free(CpsGfxSeg[1]);
		UpperFree(CpsGfxSeg[0]);
		UpperFree(CpsQSam);
		break;
	}
	CpsRom = NULL;
	CpsQSam = NULL;
	CpsGfx  = NULL;

	nCPS68KClockspeed = 0;
	Cps = 0;

	return 0;
}
