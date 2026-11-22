#pragma once
#include "library.h"

// Returns the selected index, or -1 on exit.
int menu_choose(RomLibrary *library, int selected);
void menu_error(const char *path, const char *reason);
