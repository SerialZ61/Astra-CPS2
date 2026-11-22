#pragma once

// Compile only one language into the handheld executable. The CSV format
// and the keys used to identify games, driver inputs and settings stay stable.
#ifdef ASTRA_ENGLISH
#define ASTRA_TEXT(fr, en) en
#else
#define ASTRA_TEXT(fr, en) fr
#endif

// Game screen
#define TXT_PROFILE_ACTIVE ASTRA_TEXT(\
    "[ STOP PROFIL ] Enregistrement en cours", \
    "[ STOP PROFILE ] Recording")
#define TXT_PROFILE_START ASTRA_TEXT(\
    "[ PROFIL 60 s ] Toucher pour demarrer", \
    "[ PROFILE 60 s ] Tap to start")
#define TXT_PROFILE_DONE ASTRA_TEXT(\
    "[ PROFIL 60 s ] Profil termine", \
    "[ PROFILE 60 s ] Profile saved")
#define TXT_PROFILE_ERROR ASTRA_TEXT(\
    "[ PROFIL 60 s ] Echec ecriture profil", \
    "[ PROFILE 60 s ] Could not save profile")
#define TXT_PROFILE_RESUME ASTRA_TEXT(\
    "[ PROFIL 60 s ] Reprendre le jeu", \
    "[ PROFILE 60 s ] Resume game first")
#define TXT_LOG_LINE ASTRA_TEXT(\
    "\x1b[26;1H[ NOTER ] %-29.29s", \
    "\x1b[26;1H[ LOG ] %-29.29s")
#define TXT_GAME_SHORTCUTS ASTRA_TEXT(\
    "SELECT+START  Jeux   L+R+START  Quitter\n", \
    "SELECT+START  Games   L+R+START  Quit\n")
#define TXT_RATE_VIEW ASTRA_TEXT(\
    "\x1b[12;1HCadence %-9s    Vue %-10s", \
    "\x1b[12;1HRate %-9s    View %-10s")
#define TXT_GAME_STATUS ASTRA_TEXT(\
    "\x1b[13;1H%-9s  Ecran %s   %s     ", \
    "\x1b[13;1H%-9s Screen %s  %s   ")
#define TXT_PAUSED ASTRA_TEXT(\
    "En pause", \
    "Paused")
#define TXT_PLAYING ASTRA_TEXT(\
    "En jeu", \
    "Playing")
#define TXT_NO_DSP ASTRA_TEXT(\
    "DSP indisponible", \
    "DSP unavailable")
#define TXT_CONTINUOUS ASTRA_TEXT(\
    "[ SON CONTINU ]  Toucher pour changer", \
    "[ CONTINUOUS AUDIO ] Tap to switch")
#define TXT_ARCADE_AUDIO ASTRA_TEXT(\
    "[ SON ARCADE ]   Toucher pour changer", \
    "[ ARCADE AUDIO ] Tap to switch")
#define TXT_LOG_HINT ASTRA_TEXT(\
    "Ecrire la mesure sur la SD", \
    "Save reading to SD")
#define TXT_RESUME_BUTTON ASTRA_TEXT(\
    "REPRISE", \
    "RESUME")
#define TXT_RATE_BUTTON ASTRA_TEXT(\
    "CADENCE", \
    " RATE")
#define TXT_VIEW_BUTTON ASTRA_TEXT(\
    " FORMAT", \
    " VIEW")
#define TXT_BINDINGS_BUTTON ASTRA_TEXT(\
    " REGLER", \
    " BUTTONS")
#define TXT_GAMES_BUTTON ASTRA_TEXT(\
    "  JEUX", \
    " GAMES")
#define TXT_MEASURING ASTRA_TEXT(\
    "Mesure en cours...", \
    "Measuring...")
#define TXT_WAIT_READING ASTRA_TEXT(\
    "Attendre une mesure de 2 s", \
    "Wait for a 2 s reading")
#define TXT_READING_SAVED ASTRA_TEXT(\
    "Mesure ajoutee a mesures.csv", \
    "Saved to mesures.csv")
#define TXT_READING_FAILED ASTRA_TEXT(\
    "Echec ecriture mesures.csv", \
    "Could not write mesures.csv")
#define TXT_AUDIO_COUNTS ASTRA_TEXT(\
    "Audio vides %u / pleins %u    ", \
    "Audio empty %u / full %u    ")
#define TXT_GAME_SPEED ASTRA_TEXT(\
    "Vitesse       %5.1f %%    \nEmulation     %5.1f images/s\n", \
    "Game speed    %5.1f %%    \nSimulation    %5.1f fps\n")
#define TXT_DISPLAY_RATE ASTRA_TEXT(\
    "Affichage     %5.1f images/s\nDessinees     %5.1f images/s\n", \
    "Displayed     %5.1f fps\nDrawn         %5.1f fps\n")
#define TXT_DRAW_TIME ASTRA_TEXT(\
    "Avec image    %5.1f ms\nSans image    %5.1f ms\n%s", \
    "With drawing  %5.1f ms\nNo drawing    %5.1f ms\n%s")
#define TXT_LOADING_SCREEN ASTRA_TEXT(\
    "\x1b[2J\x1b[1;1HASTRA CPS2\n\nChargement...\n%.39s", \
    "\x1b[2J\x1b[1;1HASTRA CPS2\n\nLoading...\n%.39s")
#define TXT_PROFILE_WRITE_FAILED ASTRA_TEXT(\
    "Echec ecriture profil.csv", \
    "Could not write profil.csv")

// Library
#define TXT_LIBRARY_HEADER ASTRA_TEXT(\
    "\x1b[2J\x1b[1;1H\x1b[1;36mASTRA CPS2\x1b[0m   /   JEUX SUR LA SD\n\n", \
    "\x1b[2J\x1b[1;1H\x1b[1;36mASTRA CPS2\x1b[0m   /   GAMES ON SD\n\n")
#define TXT_ROM_FOLDER ASTRA_TEXT(\
    "Place tes archives .zip dans\n/3ds/AstraCPS2/roms/\n\n", \
    "Place your ZIP archives in\n/3ds/AstraCPS2/roms/\n\n")
#define TXT_SUPPORTED ASTRA_TEXT(\
    "Jeux avec pilote", \
    "Supported games")
#define TXT_OTHER_ARCHIVES ASTRA_TEXT(\
    "Autres ZIP", \
    "Other ZIPs")
#define TXT_REFERENCE_GAME ASTRA_TEXT(\
    "* Partie verifiee sur le portable.\n", \
    "* Gameplay tested on a computer.\n")
#define TXT_NO_DRIVER ASTRA_TEXT(\
    "Revision de la collection sans pilote.\nA pour verifier le contenu.\n", \
    "No driver for this revision.\nPress A to check the contents.\n")
#define TXT_UNKNOWN_NAME ASTRA_TEXT(\
    "Nom inconnu. A pour identifier le ZIP.\n", \
    "Unknown name. Press A to identify ZIP.\n")
#define TXT_INCLUDED_DRIVER ASTRA_TEXT(\
    "Pilote inclus. Essai console a faire.\n", \
    "Driver included. Try it on hardware.\n")
#define TXT_PARENT_HINT ASTRA_TEXT(\
    "Si ZIP divise, ajouter %.12s.zip\n", \
    "For split sets, add %.12s.zip\n")
#define TXT_INCOMPLETE_LIST ASTRA_TEXT(\
    "\x1b[20;1HListe partielle (memoire insuffisante)", \
    "\x1b[20;1HPartial list (low memory)")
#define TXT_NAVIGATION ASTRA_TEXT(\
    "\x1b[22;1HHaut/bas       Choisir un ZIP\nGauche/droite  Page precedente/suivante\n", \
    "\x1b[22;1HUp/down        Select a ZIP\nLeft/right     Previous/next page\n")
#define TXT_FAMILY_KEYS ASTRA_TEXT(\
    "L / R          Changer de famille\n", \
    "L / R          Change game family\n")
#define TXT_SHOW_OTHER ASTRA_TEXT(\
    "Voir les autres ZIP", \
    "Show other ZIPs")
#define TXT_SHOW_SUPPORTED ASTRA_TEXT(\
    "Revenir aux pilotes", \
    "Show supported games")
#define TXT_LIBRARY_ACTIONS ASTRA_TEXT(\
    "\x1b[26;1HA   Lancer   X   Relire   B   Quitter", \
    "\x1b[26;1HA   Play   X   Rescan   B   Quit")
#define TXT_PLAY_BUTTON ASTRA_TEXT(\
    "  LANCER", \
    "  PLAY")
#define TXT_LOAD_HEADER ASTRA_TEXT(\
    "\x1b[2J\x1b[1;1H\x1b[1;36mASTRA CPS2\x1b[0m   /   CHARGEMENT\n\n", \
    "\x1b[2J\x1b[1;1H\x1b[1;36mASTRA CPS2\x1b[0m   /   LOADING\n\n")
#define TXT_BACK_TO_GAMES ASTRA_TEXT(\
    "%.39s\n\n%s\n\nA / B   Retour aux jeux\n", \
    "%.39s\n\n%s\n\nA / B   Back to games\n")

// Controls
#define TXT_DPAD_UP ASTRA_TEXT(\
    "Croix haut", \
    "D-pad up")
#define TXT_DPAD_DOWN ASTRA_TEXT(\
    "Croix bas", \
    "D-pad down")
#define TXT_DPAD_LEFT ASTRA_TEXT(\
    "Croix gauche", \
    "D-pad left")
#define TXT_DPAD_RIGHT ASTRA_TEXT(\
    "Croix droite", \
    "D-pad right")
#define TXT_PAD_UP ASTRA_TEXT(\
    "Pad haut", \
    "Pad up")
#define TXT_PAD_DOWN ASTRA_TEXT(\
    "Pad bas", \
    "Pad down")
#define TXT_PAD_LEFT ASTRA_TEXT(\
    "Pad gauche", \
    "Pad left")
#define TXT_PAD_RIGHT ASTRA_TEXT(\
    "Pad droite", \
    "Pad right")
#define TXT_NONE ASTRA_TEXT(\
    "Aucune", \
    "None")
#define TXT_UP ASTRA_TEXT(\
    "Haut", \
    "Up")
#define TXT_DOWN ASTRA_TEXT(\
    "Bas", \
    "Down")
#define TXT_LEFT ASTRA_TEXT(\
    "Gauche", \
    "Left")
#define TXT_RIGHT ASTRA_TEXT(\
    "Droite", \
    "Right")
#define TXT_COIN ASTRA_TEXT(\
    "Credit", \
    "Insert coin")
#define TXT_START_GAME ASTRA_TEXT(\
    "Demarrer", \
    "Start")
#define TXT_CHANGE_RATE ASTRA_TEXT(\
    "Cadence", \
    "Frame rate")
#define TXT_FORMAT ASTRA_TEXT(\
    "Format", \
    "View")
#define TXT_SETTINGS_NAV ASTRA_TEXT(\
    "A choisir   B retour   Page %d/%d\n", \
    "A select   B back   Page %d/%d\n")
#define TXT_START_SAVE ASTRA_TEXT(\
    "START enregistrer\n", \
    "START to save\n")
#define TXT_BACK ASTRA_TEXT(\
    " RETOUR", \
    " BACK")
#define TXT_SAVE ASTRA_TEXT(\
    " SAUVER", \
    " SAVE")
#define TXT_RETRY ASTRA_TEXT(\
    "Reessayer", \
    "Retry")
#define TXT_CANCEL ASTRA_TEXT(\
    "Annuler", \
    "Cancel")
#define TXT_SAVE_FAILED ASTRA_TEXT(\
    "SAUVEGARDE IMPOSSIBLE", \
    "SAVE FAILED")
#define TXT_CHECK_SD ASTRA_TEXT(\
    "Verifie l'ecriture de la carte SD.", \
    "Check that the SD card is writable.")
#define TXT_STILL_PAUSED ASTRA_TEXT(\
    "La partie reste en pause.", \
    "The game is paused.")
#define TXT_DEFAULT_BUTTONS ASTRA_TEXT(\
    "Retablir les touches par defaut", \
    "Restore default controls")
#define TXT_CONTROLS_TITLE ASTRA_TEXT(\
    "TOUCHES", \
    "BUTTONS")
#define TXT_PICK_BUTTON ASTRA_TEXT(\
    "Choisis un bouton a reaffecter.", \
    "Select a button to remap.")
#define TXT_ASSIGN ASTRA_TEXT(\
    "AFFECTER UNE ACTION", \
    "ASSIGN ACTION")
#define TXT_PICK_ACTION ASTRA_TEXT(\
    "Choisis l'action de ce bouton.", \
    "Select an action for this button.")

// Loader diagnostics
#define TXT_INIT_DRIVER ASTRA_TEXT(\
    "Initialisation du pilote", \
    "Driver initialization")
#define TXT_BLOCK_SIZE ASTRA_TEXT(\
    "%s : bloc de %u Kio. Tas total %lu Kio.", \
    "%s: %u KiB block. Total heap %lu KiB.")
#define TXT_INIT_FAILED ASTRA_TEXT(\
    "Echec : %s. Tas total %lu Kio.", \
    "Failed: %s. Total heap %lu KiB.")
#define TXT_EMULATION_ERROR ASTRA_TEXT(\
    "Erreur pendant l'emulation CPS2.", \
    "CPS2 emulation error.")
#define TXT_MISSING_PARENT ASTRA_TEXT(\
    "Ce ZIP emprunte des puces. Placez %s.zip dans le meme dossier.\nFichier absent ou illisible.", \
    "This ZIP needs chips from %s.zip.\nPlace it in the same folder and check that it can be read.")
#define TXT_MISSING_CHIP ASTRA_TEXT(\
    "%s incomplet ou autre revision. Puce : %s (%08lx).%s%s%s", \
    "%s incomplete or wrong revision. Missing chip: %s (%08lx).%s%s%s")
#define TXT_PARENT ASTRA_TEXT(\
    " Parent : ", \
    " Parent: ")
#define TXT_REOPEN_FAILED ASTRA_TEXT(\
    "Impossible de rouvrir le ZIP.", \
    "Could not reopen ZIP.")
#define TXT_BAD_SELECTION ASTRA_TEXT(\
    "Selection de jeu invalide.", \
    "Invalid game selection.")
#define TXT_BAD_DIRECTORY ASTRA_TEXT(\
    "Impossible de lire le repertoire du ZIP.", \
    "Could not read ZIP directory.")
#define TXT_BAD_MARVEL ASTRA_TEXT(\
    "Marvel vs. Capcom Europe : copie connue de mvce.04a avec une erreur.\nCRC lu CAC02153, attendu 436C5A4E.", \
    "Marvel vs. Capcom Europe: known bad copy of mvce.04a.\nCRC CAC02153; expected 436C5A4E.")
#define TXT_GIGA_FILLER ASTRA_TEXT(\
    "Giga Man 2 : ce ZIP contient du remplissage pour les decors et le son. Cette carte utilise aussi un son OKI.", \
    "Giga Man 2: the graphics and sound files contain filler. This board also uses OKI audio.")
#define TXT_GIGA_BOARD ASTRA_TEXT(\
    "Giga Man 2 : carte speciale a son OKI, sans pilote dans Astra.", \
    "Giga Man 2: custom board with OKI audio. Astra has no driver for it.")
#define TXT_UNSUPPORTED ASTRA_TEXT(\
    "Jeu ou revision CPS2 non pris en charge.", \
    "Unsupported CPS2 game or revision.")
#define TXT_READ_FAILED ASTRA_TEXT(\
    "Lecture ou CRC incorrect : %s (%08lx).", \
    "Read or CRC error: %s (%08lx).")
#define TXT_PREPARE_68000 ASTRA_TEXT(\
    "Preparation du programme 68000", \
    "68000 program setup")
#define TXT_GRAPHICS_MEMORY ASTRA_TEXT(\
    "Memoire des decors", \
    "Graphics memory")
#define TXT_PROGRAM_MEMORY ASTRA_TEXT(\
    "Memoire des programmes et echantillons", \
    "Program and sample memory")
#define TXT_CHIP_LIST ASTRA_TEXT(\
    "Inventaire des puces", \
    "Chip inventory")
#define TXT_READ_CHIPS ASTRA_TEXT(\
    "Lecture des puces", \
    "Chip loading")
#define TXT_CPU_68000 ASTRA_TEXT(\
    "Processeur 68000", \
    "68000 CPU")
#define TXT_BOARD_MEMORY ASTRA_TEXT(\
    "Memoire de la borne", \
    "Arcade board memory")
#define TXT_EEPROM_MEMORY ASTRA_TEXT(\
    "Memoire EEPROM", \
    "EEPROM memory")
#define TXT_INIT_QSOUND ASTRA_TEXT(\
    "Initialisation QSound", \
    "QSound setup")
