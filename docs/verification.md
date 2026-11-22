# How v0.6 was checked · Vérification de la v0.6

SerialZ selected the French build as the functional Old 3DS reference after playing on the console. Its SHA-256 is `11faa88879cd89bbf3b62e3af9ffe698647cd9ab3d5be9c4e9997cb907bf880e`. The English build translates the frontend and loader messages from the same sources. Game code and language come from each player's arcade set.

The English executable was exercised in Azahar's Old 3DS profile with Street Fighter Zero 3 Japan in Auto, 30 fps and All with continuous audio. All three readings were saved successfully. Its SHA-256 is `d189c15c22b8abc77a14f550186ea32f92430b0661c7434e3749e004a8818922`. Physical-console feedback for this release refers to the French executable.

## From the first credit to v0.6

The first target was one credit and a playable match in *Street Fighter Alpha* from the original ZIP. PiFBA supplied the arcade drivers, CPU emulation and QSound. The 3DS port added its own ZIP library, per-revision controls, display and stereo output. Real play exposed two different problems. Drawing every frame could slow the fight, and larger games could fail to open after switching titles.

To address the first, Astra runs the controls and arcade sound for every emulated frame and schedules the pictures independently. On recognised revisions it can also shorten repeated CPU work while the arcade program waits. The loader streams graphics from the archives and reserves space for large mandatory allocations before optional caches. The v0.5 memory test repeatedly switched between Alpha 3, X-Men vs. Street Fighter, Shadow over Mystara and Zero 2 Alpha in one process with fragmented memory. The same switching sequence still passes with v0.6. The new tile and palette work then reduced the cost of drawing a frame across game families.

**Côté console.** On est parti d’une pièce dans *Street Fighter Alpha*. Puis les essais ont montré deux soucis distincts : le combat ralentissait quand la 3DS dessinait trop d’images et certains gros jeux refusaient de démarrer après un changement de titre. Astra a séparé la cadence du jeu de celle du dessin, lit les décors par morceaux et réserve d’abord la mémoire indispensable. La v0.6 s’attaque ensuite au prix d’une image complète, tout en gardant le QSound stéréo.

## Replaying the same fight

We ran the ARM binaries for v0.5 and v0.6 with the same ROM revision, inputs and drawing schedule. For each of seven games we replayed 2,000 arcade frames, drew every other frame, and collected stereo samples on every frame. The hashes of the 1,000 images, the stereo samples, the selected arcade RAM regions and the Z80 state matched across versions for each game.

For both versions we counted instructions from executed ARM blocks in four drawn frames (1,350, 1,710, 1,718 and 1,920). The percentages below are reductions summed across those frames. The right column covers only the arcade draw routine inside the whole core. These counts describe CPU work. Frame rates on a physical console also depend on memory access, audio output and presentation.

| Arcade set | Fewer estimated ARM instructions, whole core | Fewer estimated ARM instructions, draw routine |
|---|---:|---:|
| Street Fighter Zero 3 Japan (`sfz3j`) | 25.04% | 34.65% |
| X-Men vs. Street Fighter USA Phoenix (`xmvsfu1d`) | 17.51% | 25.70% |
| Street Fighter Zero 2 Alpha Japan (`sfz2alj`) | 17.97% | 28.54% |
| 1944 (`1944`) | 25.32% | 35.27% |
| Alien vs. Predator (`avsp`) | 21.18% | 34.49% |
| Progear (`progear`) | 22.54% | 32.48% |
| Giga Wing (`gigawing`) | 22.35% | 34.89% |

The continuous-audio test produced the same **496,587 stereo sample pairs** in both versions. A separate drawing test covered tile sizes, flips, clipping, palette changes, priority and the fallback when optional cache allocations fail.

To exercise one game on your workstation, install Python with `unicorn`, `pyelftools` and `Pillow`, build the ELF, and supply your own ZIP and any required parent ZIP in the same directory. Run this from the repository root. The JSON contains hashes and counts for the sampled frames.

```sh
python tests/audio_work.py out/AstraCPS2.elf /path/to/roms/sfz3j.zip sfz3j-results.json
```

## What the original 3DS measured

These short, player-triggered readings are **from v0.5** on the original 3DS. Street Fighter Zero 3 Japan was played with continuous sound. Each reading covers roughly two seconds. The selections of moves and scenes varied.

| Pacing | Arcade speed | Pictures sent to the screen/s | Empty audio queue events |
|---|---:|---:|---:|
| Auto | 99.67–100.31% | 17.98–23.92 | 0 |
| 30 fps | 64.97–72.45% | 29.80 | 0 |
| All | 59.67–59.69% | 35.58–35.59 | 0 |

In Azahar's Old 3DS profile, v0.5 already gave 59.61 displayed pictures/s in All on the scripted run. Workstation replays verify rendering and sound; original-hardware CSVs measure play speed. With v0.6, tap **PROFILE 60 s** / **PROFIL 60 s** during a match to record approximately one row per second. Archive, pacing and sound mode appear on each row. Draw time is included in core time. Video-call time is measured on the CPU; the GPU can complete its work later.

## ZIP compatibility

The v0.6 ARM collection test checked ZIP integrity, opened each of 240 archives and requested two frames from each supported revision. **238 booted** and returned the expected number of stereo sample pairs. The table records the two known refusals and any companion ZIP used in this collection. A two-frame boot test establishes loading and initial execution. Performance and completion of a game require longer play. [Results for all 240 archives](compatibility.csv)

**En français.** Les deux versions ont rejoué les mêmes commandes sur sept jeux. Les images, le son stéréo et l’état du jeu comparé sont identiques. Les pourcentages du premier tableau mesurent l’économie de travail du processeur sur quatre trames dessinées par jeu. Les chiffres du deuxième tableau proviennent de la vraie Old 3DS en v0.5. La v0.6 française est la version retenue après l’essai sur console. Le bouton **PROFIL 60 s** permet de mesurer un combat sur sa propre machine.
