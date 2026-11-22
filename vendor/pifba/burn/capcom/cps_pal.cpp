#include "cps.h"
#ifdef ASTRA_CPS2
void AstraTilePaletteChanged(unsigned bank);
void AstraTilePaletteReset();
void AstraTileClose();
#endif
// CPS (palette)

static unsigned char* CpsPalSrc = NULL;			// Copy of current input palette

unsigned int* CpsPal = NULL;					// Hicolor version of palette
unsigned int* CpsObjPal = NULL;

int nLagObjectPalettes;

inline static unsigned int CalcCol(unsigned short a)
{
	int r, g, b, f;
	const int F_OFFSET = 0x0F;

	// Format is FFFF RRRR GGGG BBBB
	f = (a & 0xF000) >> 12;

	r = (a & 0x0F00) >> 4;		// Red
	r |= r >> 4;
	g = (a & 0x00F0);		// Green
	g |= g >> 4;
	b = (a & 0x000F);		// Blue
	b |= b << 4;

	f += F_OFFSET;
	r *= f; r /= F_OFFSET + 0x0F;
	g *= f; g /= F_OFFSET + 0x0F;
	b *= f; b /= F_OFFSET + 0x0F;

	return BurnHighCol(r, g, b, 0);
}

static int CalcAll()
{
#ifdef ASTRA_CPS2
    AstraTilePaletteReset();
#endif
	unsigned short* ps;

	if (Cps == 2) {
		if (nLagObjectPalettes) {
			ps = (unsigned short*)CpsPalSrc + 0x0C00;
			for (int i = 0x0C00; i < 0x0E00; i++, ps++) {
				CpsPal[i ^ 15] = CalcCol(*ps);
			}
			ps = (unsigned short*)CpsPalSrc + 0x0200;
			for (int i = 0x0200; i < 0x0800; i++, ps++) {
				CpsPal[i ^ 15] = CalcCol(*ps);
			}

			memcpy(CpsPal + 0x0E00, CpsPal + 0x0C00, 0x0200 << 2);
		} else {
			ps = (unsigned short*)CpsPalSrc;
			for (int i = 0x0000; i < 0x0800; i++, ps++) {
				CpsPal[i ^ 15] = CalcCol(*ps);
			}
		}

	} else {
		ps = (unsigned short*)CpsPalSrc;
		for (int i = 0x0000; i < 0x0800; i++, ps++) {
			CpsPal[i ^ 15] = CalcCol(*ps);
		}
	}

	return 0;
}

static void CalcAllStar(int nLayer)
{
	unsigned short* ps = (unsigned short*)CpsPalSrc;
	int nOffset = 0x0800 + (nLayer << 9);

	for (int i = 0; i < 128; i++, ps++) {
		CpsPal[(i + nOffset) ^ 15] = CalcCol(*(ps + nOffset));
	}
}

int CpsPalInit()
{
	int nLen = 0;

	nLen = 0x1000 * sizeof(short);
	CpsPalSrc = (unsigned char*)malloc(nLen);
	if (CpsPalSrc == NULL) {
		return 1;
	}
	memset(CpsPalSrc, 0, nLen);

	// The star layer palettes are at the end of the normal palette, so double the size
	nLen = 0x1000 * sizeof(int);
	CpsPal = (unsigned int*)malloc(nLen);
	if (CpsPal == NULL) {
		return 1;
	}

	// Set CpsPal to initial values
	CalcAll();
	if (CpsStar) {
		CalcAllStar(0);
		CalcAllStar(1);
	}

	if (nLagObjectPalettes) {
		CpsObjPal = CpsPal + 0x0C00;
	} else {
		CpsObjPal = CpsPal;
	}

	return 0;
}

int CpsPalExit()
{
#ifdef ASTRA_CPS2
	AstraTileClose();
#endif
	if (CpsPal) {
		free(CpsPal);
		CpsPal = NULL;
	}
	if (CpsPalSrc) {
		free(CpsPalSrc);
		CpsPalSrc = NULL;
	}
	return 0;
}

// Each bank of 16 pens shares one revision in the renderer. Skip an
// unchanged bank eight words at a time, then rebuild only changed colours.
static void updateBanks(const unsigned short *incoming, unsigned first, unsigned count)
{
    unsigned short *saved = (unsigned short *)CpsPalSrc + first;
    for (unsigned i = 0; i < count; i += 16) {
        const auto *oldWords = reinterpret_cast<const unsigned *>(saved + i);
        const auto *newWords = reinterpret_cast<const unsigned *>(incoming + i);
        unsigned different = 0;
        for (unsigned w = 0; w < 8; ++w) different |= oldWords[w] ^ newWords[w];
        if (!different) continue;
        for (unsigned pen = i; pen < i + 16; ++pen) {
            unsigned short colour = incoming[pen];
            if (saved[pen] == colour) continue;
            saved[pen] = colour;
            CpsPal[(first + pen) ^ 15] = CalcCol(colour);
        }
        AstraTilePaletteChanged((first + i) >> 4);
    }
}

// Update CpsPal with the new palette at pNewPal (length 0x1000 bytes)
int CpsPalUpdate(unsigned char* pNewPal, int bRecalcAll)
{
	unsigned short *ps, *pn;

	// If we are recalculating the whole palette, just copy to CpsPalSrc
	// and recalculate it all
	if (bRecalcAll) {
		ps = (unsigned short*)CpsPalSrc;
		pn = (unsigned short*)pNewPal;

		if (nLagObjectPalettes) {
			int nBuffer = 0x0C00 + ((GetCurrentFrame() & 1) << 9);

			memcpy(ps + 0x0200, pn + 0x0200, 0x0600 << 1);
			memcpy(ps + nBuffer, pn, 0x0200 << 1);
			memcpy(ps + 0x0E00, pn, 0x0200 << 1);

			CpsObjPal = CpsPal + nBuffer;
		} else {
			memcpy(ps, pn, 0x0800 << 1);
		}

		CalcAll();

		return 0;
	}

	pn = (unsigned short*)pNewPal;
    if (Cps == 2 && nLagObjectPalettes) {
        unsigned current = 0x0C00 + ((GetCurrentFrame() & 1) << 9);
        updateBanks(pn, current ^ 0x0200, 0x0200);
        updateBanks(pn + 0x0200, 0x0200, 0x0600);
        CpsObjPal = CpsPal + current;
    } else {
        updateBanks(pn, 0, 0x0800);
    }

	return 0;
}

int CpsStarPalUpdate(unsigned char* pNewPal, int nLayer, int bRecalcAll)
{
	int i;
	unsigned short *ps, *pn;

	if (nLayer == 0) {
		ps = (unsigned short*)CpsPalSrc + 0x0800;
		pn = (unsigned short*)pNewPal + 0x0800;

		if (bRecalcAll) {
			memcpy(ps, pn, 256);
			CalcAllStar(nLayer);
			return 0;
		}

		// Star layer 0
		for (i = 0x0800; i < 0x0880; i++, ps++, pn++) {
			unsigned short n = *pn;
			if (*ps == n) {
				   continue;					// Colour hasn't changed - great!
			}

			*ps = n;							// Update our copy of the palette

			CpsPal[i ^ 15] = CalcCol(n);
		}
	} else {
		ps = (unsigned short*)CpsPalSrc + 0x0A00;
		pn = (unsigned short*)pNewPal + 0x0A00;

		if (bRecalcAll) {
			memcpy(ps, pn, 256);
			CalcAllStar(nLayer);
			return 0;
		}

		// Star layer 1
		for (i = 0x0A00; i < 0x0A80; i++, ps++, pn++) {
			unsigned short n = *pn;
			if (*ps == n) {
				   continue;					// Colour hasn't changed - great!
			}

			*ps = n;							// Update our copy of the palette

			CpsPal[i ^ 15] = CalcCol(n);
		}
	}

	return 0;
}

