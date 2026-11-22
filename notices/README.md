# Credits and redistribution · Crédits et redistribution

**SerialZ** directed the project and played it on an original Nintendo 3DS. **Codex (OpenAI)** contributed to development, optimisation, the test tools, translation and packaging. Astra CPS2 follows [Astra CPS1](https://github.com/SerialZ61/Astra-CPS1).

The components have their own terms. The original FB Alpha notice sets conditions for noncommercial distribution, publishing source changes and including its complete notice. Both language packages include the corresponding modified source and notices. Players supply their own arcade data and 3DS DSP firmware. Game titles and trademarks belong to their respective owners.

Chaque composant conserve ses conditions. Le texte FB Alpha précise les conditions de redistribution non commerciale, de publication des modifications et de reproduction de sa notice complète. Les deux archives incluent les sources modifiées et les notices. Les joueurs fournissent leurs propres fichiers d’arcade et le micrologiciel audio de leur console.

| Component | Credits and source |
|---|---|
| Arcade emulation | Dave (Final Burn), Team FB Alpha, MAME contributors, HeadOverHeels (FBA2X), Squid (PiFBA). [FB Alpha](FB-Alpha-license.txt) · [PiFBA](PiFBA.txt) · [upstream source](https://github.com/squidrpi/pifba/tree/9d3dd8476750adf29253c8922841b87ff36b930b) |
| Motorola 68000 and Z80 | Dave and notaz ([Cyclone](Cyclone.txt)), Juergen Buchmueller ([Z80](Z80.txt)), Stéphane Dallongeville ([CZ80](CZ80.txt)) |
| CPS2 opcode decryption | Andreas Naive, Nicola Salmoria, Charles MacDonald and Razoola. The port uses PiFBA's implementation and adapts additional public revision constants from [MAME 0.139](https://github.com/mamedev/mame/blob/mame0139/src/mame/machine/cps2crpt.c). [Historical MAME notice](MAME-historical.txt) |
| Additional set metadata | Paul Leaman, Andreas Naive and Nicola Salmoria. Names, sizes and checksums in the additional revision definitions derive from [the MAME CPS2 driver](https://github.com/mamedev/mame/blob/774a180df2b6ef9c53e48337792256817c50f768/src/mame/capcom/cps2.cpp). [BSD 3-Clause](MAME-driver-BSD.txt) |
| ZIP reader and compression | Gilles Vollant ([MiniZip](MiniZip.txt)), Jean-loup Gailly and Mark Adler ([zlib](zlib.txt)) |
| Console runtime, graphics and toolchain | devkitPro and the 3DS homebrew contributors. [libctru](libctru.txt) · [citro3d](citro3d.txt) · [picasso](picasso.txt) · [newlib](newlib.txt) · [GCC](GCC-GPLv3.txt) and [runtime exception](GCC-runtime-exception.txt) |

The upstream source files retain their author credits and component-specific notices.
