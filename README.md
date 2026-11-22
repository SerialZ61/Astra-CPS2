# Astra CPS2 for the original Nintendo 3DS

**[Download v0.6 in English](https://github.com/SerialZ61/Astra-CPS2/releases/download/v0.6/Astra-CPS2-v0.6-EN.zip)** · [Download v0.6 in French](https://github.com/SerialZ61/Astra-CPS2/releases/download/v0.6/Astra-CPS2-v0.6-FR.zip) · [Lire en français](README.fr.md) · [Astra CPS1](https://github.com/SerialZ61/Astra-CPS1)

Astra CPS2 brings Capcom Play System 2 arcade games to the original Nintendo 3DS under Luma3DS. It sits alongside Astra CPS1 as a separate application. Play from your own unmodified arcade ZIPs with stereo QSound and per-game controls, including all six buttons in Street Fighter.

## Install and play

1. Choose one of the two language packages above. Extract its `3ds` folder to the root of your SD card. Both editions use `/3ds/AstraCPS2/AstraCPS2.3dsx` and share the same games and button mappings.
2. Put your game ZIPs in `/3ds/AstraCPS2/roms/`. Leave them compressed. For sound, the console needs its own DSP firmware at `/3ds/dspfirm.cdc`.
3. Open **Astra CPS2** in the Homebrew Launcher. One detected ZIP launches automatically. With several ZIPs, choose one with the D-pad and press **A**. **X** rescans the SD card.
4. Press **SELECT** to insert a coin, release it, then press **START**. **SELECT + START** returns to the library. **L + R + START** exits to the Homebrew Launcher.

*Street Fighter Alpha* uses this six-button layout by default.

| Attack | Light | Medium | Heavy |
|---|---|---|---|
| Punch | Y | X | L |
| Kick | B | A | R |

Tap **BUTTONS** on the lower screen to remap the controls. Choose an input and its arcade action, then save. Each revision has its own mapping under `/3ds/AstraCPS2/config/`. The game's dialogue and menus follow its arcade revision.

### If a ZIP will not start

Some arcade archives contain only the chips that differ from another revision of the same game. Keep both ZIPs side by side. For example, `sfz2alj.zip` needs `sfz2al.zip` in the tested split set. Astra checks the size and CRC of the files inside each ZIP. The failure message is also recorded in `/3ds/AstraCPS2/echecs.csv`.

The v0.6 desktop boot test opened **238 of 240 archives** and ran two arcade frames for each successful boot. In that collection, one European *Marvel vs. Capcom* archive had a bad program chip (`mvce.04a`). The `mvscr1.zip` revision worked with the parent beside it. The tested `gigamn2.zip` contained filler for graphics and sound and targets a board with OKI audio. Full-speed gameplay depends on the scene and the console. [Compatibility by revision](docs/compatibility.csv)

## What changed in v0.6?

Picture a brick wall behind the fighters. The arcade game builds it from little squares called **tiles**. A tile says which colour to use at each pixel. Astra keeps a coloured copy so the next identical brick is cheap to draw. In v0.6, when Astra needs to prepare a tile, it can look up **two pixels' colours at once**. When the game changes a palette, Astra refreshes the colours that changed. It can also copy a visible stretch of a tile straight to the picture. The 3DS GPU scales the finished picture to 4:3.

We exercised that change by replaying the same inputs on the compiled ARM code in v0.5 and v0.6. Each of seven games ran for 2,000 arcade frames. All 1,000 rendered images and all stereo samples matched byte for byte in each replay. Across four sampled frames that included drawing, the estimated count of ARM instructions executed by the emulation core fell by **25.0% in Street Fighter Zero 3 (Japan)**, **17.5% in X-Men vs. Street Fighter (USA Phoenix)** and **25.3% in 1944**. Those percentages describe the work in the sampled frames. Actual frame rates are measured on an Old 3DS. [Verification and measurements](docs/verification.md)

## Reading the numbers on the lower screen

At arcade speed, the game advances about **59.6 frames per second**. **Auto** adjusts how often to draw, **30 fps** targets about 29.8 pictures per second, and **All** requests a picture every arcade frame. All three modes read the buttons and run the arcade sound on every emulated frame. **Continuous audio** can stretch stereo output when the game falls behind.

For example, on a physical Old 3DS under v0.5, *Street Fighter Zero 3* reached **99.7–100.3% game speed** in Auto while displaying **18–24 pictures/s**. In All it displayed about **35.6 pictures/s** while the fight ran at **59.7%** of arcade speed. That difference is why Astra shows both counters.

To report a slow scene, select the frame and sound modes, then tap **PROFILE 60 s** at the start of a round. Play normally. Astra collects roughly one reading per second in memory and writes `/3ds/AstraCPS2/profil.csv` when the capture ends. Tap again to stop early. **LOG** saves the last complete two-second window to `mesures.csv`. Both editions keep the French CSV field names for comparison. In `profil.csv`, `vitesse_pct` is game speed, `affichage_ips` counts frames sent to the screen per second, and `audio_vides` counts how often the audio queue ran dry. Include the ZIP name, stage or fighters, mode and any audible gaps with the relevant CSV rows.

## Build and credits

Install devkitPro's 3DS toolchain with devkitARM, libctru, citro3d, picasso, 3DS zlib, `smdhtool` and `3dsxtool`. From the repository root in the devkitPro shell, run `make -j4` for the French edition or `make -j4 UI_LANG=en` for English. In PowerShell, use `.\build.ps1` or `.\build.ps1 -Language en`. The executables are `out/AstraCPS2.3dsx` and `out/en/AstraCPS2.3dsx`, respectively.

SerialZ directed the project and played the hardware tests. Codex (OpenAI) worked on the 3DS port, profiling and regression tests. The arcade emulation builds on Final Burn, FB Alpha and PiFBA, including the Cyclone 68000 core and MAME-derived Z80 code. The 3DS frontend uses devkitPro's libctru and citro3d. Third-party terms, including FB Alpha's non-commercial terms, apply to their respective components. [Credits and licences](notices/README.md)
