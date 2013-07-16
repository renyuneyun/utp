/* main.c */
#define STDIO_H
#include <stdio.h>
#define STRING_H
#include <string.h>
#include "dec.h"

#define DEBUG(M) printf("##%d##\n", M);

int main(int argc, char **argv)
{
	char **page;
	int iarg = 1, lnum = 0, length;
	int cnum[4];
	if (!(argc & 1)) {
		deal_error();
		return 0;
	}
	readpage(&page, &lnum, &length);
	basic_count(page, lnum, cnum);
	print_count(cnum);
	print_page(page, lnum);
	--argc;
	while (iarg < argc) {
		if (!strcmp(argv[iarg], "-d")) {
			del(page, lnum, argv[iarg + 1]);
			basic_count(page, lnum, cnum);
			print_count(cnum);
			print_page(page, lnum);
		} else {
			if (!strcmp(argv[iarg], "-s")) {
				printf("The string \"%s\" appears %d times\n", argv[iarg + 1], count_string(page, lnum, argv[iarg + 1]));
			}
		}
		iarg += 2;
	}
	clean(page, lnum);
	return 0;
}
