# Astra CPS2 pour la Nintendo 3DS d’origine

**[Télécharger la v0.6 en français](https://github.com/SerialZ61/Astra-CPS2/releases/download/v0.6/Astra-CPS2-v0.6-FR.zip)** · [Télécharger la v0.6 en anglais](https://github.com/SerialZ61/Astra-CPS2/releases/download/v0.6/Astra-CPS2-v0.6-EN.zip) · [Read in English](README.md) · [Astra CPS1](https://github.com/SerialZ61/Astra-CPS1)

Après Astra CPS1, les jeux d’arcade Capcom Play System 2 arrivent sur **Old 3DS sous Luma3DS**, dans une application à part. Astra CPS2 lit tes ZIP d’origine, joue le QSound en stéréo et mémorise les commandes par jeu. Les six boutons de Street Fighter tiennent sur la console 🙂

## Installer et lancer une partie

1. Choisis l’une des deux langues ci-dessus. Copie le dossier `3ds` du paquet à la racine de ta carte SD. Les deux éditions utilisent `/3ds/AstraCPS2/AstraCPS2.3dsx`, les mêmes jeux et les mêmes réglages de touches.
2. Place tes ZIP dans `/3ds/AstraCPS2/roms/`. Garde-les compressés. Pour le son, la console utilise son propre micrologiciel DSP dans `/3ds/dspfirm.cdc`.
3. Ouvre **Astra CPS2** depuis le Homebrew Launcher. Si Astra trouve un seul ZIP, la partie se lance directement. S’il y en a plusieurs, choisis le jeu avec la croix et valide avec **A**. **X** relit la carte.
4. Appuie sur **SELECT** pour mettre une pièce, relâche, puis appuie sur **START**. **SELECT + START** te ramène à la liste des jeux. **L + R + START** quitte vers le Homebrew Launcher.

Voici les touches par défaut dans *Street Fighter Alpha*.

| Attaque | Léger | Moyen | Fort |
|---|---|---|---|
| Poing | Y | X | L |
| Pied | B | A | R |

Pour les changer, touche **RÉGLER** sur l’écran du bas. Choisis une touche, son action, puis sauvegarde. Chaque révision a son propre fichier dans `/3ds/AstraCPS2/config/`. La langue des dialogues et des menus du jeu dépend de sa révision arcade.

### Si un ZIP refuse de démarrer

Certaines archives ne contiennent que les puces qui changent d’une révision à l’autre. Laisse le ZIP qui fournit les autres puces juste à côté. Par exemple, dans la collection testée, `sfz2alj.zip` emprunte des fichiers à `sfz2al.zip`. Astra vérifie la taille et l’empreinte CRC des fichiers qu’il lit. En cas d’échec, tu retrouveras aussi le message de la console dans `/3ds/AstraCPS2/echecs.csv`.

Sur le portable, le test de démarrage de la v0.6 a lancé **238 archives sur 240** et exécuté les deux premières trames de chacune. Dans cette collection, une copie européenne de *Marvel vs. Capcom* contenait une puce erronée (`mvce.04a`). La révision `mvscr1.zip` a démarré avec le ZIP parent à côté. Le `gigamn2.zip` testé contenait du remplissage pour les décors et le son et provenait d’une carte à son OKI. Pour savoir à quelle vitesse tourne un niveau, il faut y jouer sur la console. [Compatibilité par révision](docs/compatibility.csv)

## Qu’a-t-on accéléré en v0.6 ?

Imagine le mur de briques derrière deux combattants. Pour le construire, la borne répète de petits carrés appelés **tuiles**. Chaque tuile indique quelle couleur mettre à chaque point. Astra garde la brique coloriée en mémoire pour la réutiliser au prochain endroit du mur. Avec la v0.6, quand il faut préparer une tuile, la 3DS peut retrouver la couleur de **deux points d’un coup**. Si le jeu change sa palette, Astra recalcule les couleurs qui ont changé. Il peut aussi copier directement un bout de ligne visible. La puce graphique de la 3DS met ensuite l’image au format 4:3.

On a rejoué les mêmes commandes sur le code ARM des versions 0.5 et 0.6 pendant 2 000 trames d’arcade sur chacun de sept jeux. Les 1 000 images dessinées et tous les échantillons sonores stéréo de chaque partie sont identiques entre les deux versions. Sur quatre trames dessinées prises aux mêmes instants, le nombre estimé d’instructions ARM exécutées par le moteur a baissé de **25,0 % dans Street Fighter Zero 3 (Japon)**, **17,5 % dans X-Men vs. Street Fighter (USA Phoenix)** et **25,3 % dans 1944**. Ces chiffres décrivent le travail économisé sur ces trames. La vitesse réelle se mesure sur Old 3DS. [Vérifications et mesures](docs/verification.md)

## Lire les chiffres de l’écran du bas

À la vitesse de la borne, le jeu avance d’environ **59,6 trames par seconde**. **Auto** ajuste le nombre de dessins au temps disponible. **30 i/s** vise environ 29,8 images affichées par seconde. **Toutes** demande un dessin à chaque trame. Dans les trois modes, le jeu lit tes touches et produit le son d’arcade à chaque trame émulée. **Son continu** peut étirer le son stéréo quand le jeu ralentit.

Sur une vraie Old 3DS en v0.5, *Street Fighter Zero 3* tenait **99,7 à 100,3 % de la vitesse de la borne** en Auto avec **18 à 24 images/s à l’écran**. En mode Toutes, il affichait environ **35,6 images/s** et le combat tournait à **59,7 %**. C’est pour ça qu’Astra affiche les deux chiffres.

Pour signaler un passage lent, choisis ta cadence et ton mode son, puis touche **PROFIL 60 s** au début d’un round. Joue normalement. Astra garde environ un relevé par seconde en mémoire et écrit `/3ds/AstraCPS2/profil.csv` à la fin. Tu peux toucher le bouton à nouveau pour arrêter plus tôt. **NOTER** enregistre la dernière fenêtre complète de deux secondes dans `mesures.csv`. Les colonnes restent en français dans les deux éditions. Dans `profil.csv`, `vitesse_pct` donne la vitesse du jeu, `affichage_ips` le nombre d’images envoyées à l’écran par seconde et `audio_vides` le nombre de fois où la réserve de son s’est vidée. Pour partager ton essai, copie les lignes du CSV en précisant le nom du ZIP, le niveau ou les combattants, les modes choisis et ce que tu as entendu.

## Compiler et retrouver les auteurs

Installe les outils 3DS de devkitPro avec devkitARM, libctru, citro3d, picasso, zlib pour 3DS, `smdhtool` et `3dsxtool`. À la racine du dépôt, dans le shell devkitPro, lance `make -j4` pour le français ou `make -j4 UI_LANG=en` pour l’anglais. Dans PowerShell, utilise `.\build.ps1` ou `.\build.ps1 -Language en`. Les exécutables se trouvent respectivement dans `out/AstraCPS2.3dsx` et `out/en/AstraCPS2.3dsx`.

SerialZ a dirigé le projet et joué les parties d’essai sur console. Codex (OpenAI) a travaillé sur le portage 3DS, les mesures et les tests de non-régression. Le moteur d’arcade s’appuie sur Final Burn, FB Alpha et PiFBA, avec Cyclone pour le 68000 et un cœur Z80 issu de MAME. L’interface 3DS utilise libctru et citro3d de devkitPro. Chaque composant conserve ses conditions de distribution, dont les conditions non commerciales de FB Alpha. [Crédits et licences](notices/README.md)
