/* main.c */
#include "ui.h"

int main(int argc, char **argv)
{
	if (argc == 1) {
		interactive();
	} else {
		parametric(argc, argv);
	}
	return 0;
}
