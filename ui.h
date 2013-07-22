#ifndef UI_H
#define UI_H
#include <stdio.h>
#include "dec.h"
#include "def.h"
void show_welcome();
void show_version();
void ihelp();
int interactive();
void phelp(int argc, char **argv);
int parametric(int argc, char **argv);
void blank_page();
#endif
