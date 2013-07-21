/* ui.c */
#ifndef UI
#define UI
#include <stdio.h>
#include "ui.h"
#include "dec.h"
#include "def.h"

void show_version() {
	printf("an Ugly Text Processor\n");
	printf("Verson: 0.30\n");
	printf("\nReport bugs or give advice to renyuneyun@gmail.com\n");
	printf("Have a good day:P\n");
}
void show_welcome() {
	printf("Welcome to use the Ugly Text Processor!\n");
	printf("Type 'help' to view a list of commands.\n");
}
void ihelp() {
	printf("possible commands are:\n");
	printf(BLANK"new\t\t\tstart a new page\n\t\t\t\tempty lines will be ignored\n");
	printf(BLANK"append\t\tappend some lines to the existing page\n\t\t\t\tempty lines will be ignored\n");
	printf(BLANK"print\t\t\tprint the current page\n");
	printf(BLANK"count\t\t\tprint the number of English characters, blank, \n\t\t\tArabic numerals, and all characters\n");
	printf(BLANK"search\t\tshow how many times a string appears\n");
	printf(BLANK"delete\t\tdelete one certain string in the page\n");
	printf(BLANK"remove\t\tremove one line\n");
	printf(BLANK"help\t\t\tshow this page\n");
	printf(BLANK"version\t\tshow the version information\n");
	printf(BLANK"quit\t\t\tquit the program\n");
}
int interactive() {
	char **page = NULL, line[81];
	int icommand, lnum = 0, length, itimes, linenum;
	int cnum[4];
	show_welcome();
	while ((printf("("PROGNAME")")) && (icommand = readcommand())) {
		switch (icommand) {
			case COM_NULL :
				break;
			case COM_ERROR :
				printf("Unknown Command!\n");
				printf("type 'help' for help\n");
				break;
			case COM_QUIT :
				return 0;
				break;
			case COM_HELP :
				ihelp();
				break;
			case COM_VERSION :
				show_version();
				break;
			case COM_PRINT :
				if (page)
					print_page(page, lnum);
				else
					blank_page();
				break;
			case COM_NEW :
				printf("type your page below:(use two empty lines to finish typing)\n");
				clean(&page, &lnum);
				page = NULL;
				lnum = readpage(&page, lnum);
				break;
			case COM_COUNT :
				if (page) {
					basic_count(page, lnum, cnum);
					print_count(cnum);
				} else
					blank_page();
				break;
			case COM_DELETE :
				if (page) {
					printf("type the string you want to delete: ");
					if (readline(line) > -1)
						del(page, lnum, line);
				} else
					blank_page();
				break;
			case COM_SEARCH :
				if (page) {
					printf("type the string you want to search for below:\n");
					readline(line);
					itimes = count_string(page, lnum, line);
					printf("The string \"%s\" appears %d time(s)\n", line, itimes);
				} else
					blank_page();
				break;
			case COM_APPEND :
				printf("type what you want to add below: (use two empty lines to finish typing)\n");
				lnum = readpage(&page, lnum);
				break;
			case COM_REMOVE :
				if (page) {
					printf("type the number of the line you want to remove: (the first line is line 1)\n");
					linenum = readnum();
					if ((linenum > 0) && (linenum <= lnum))
						removeline(&page, &lnum, linenum);
					else
						printf("no such line\n");
				} else {
					blank_page();
				}
				break;
		}
	}
	clean(&page, &lnum);
	return 1;
}
void phelp(int argc, char **argv) {
	printf("an Ugly Text Processor\n");
	printf("If you want to use the interactive mode, start the program with NO parameters\n");
	printf("This program reads from stdin. Two empty lines means to stop reading.\n");
	printf("Empty lines will be ignored.\n");
	printf("\nUsage:\n");
	printf("%s [-option] [-s <string>] [-d <string>]\n", argv[0]);
	printf("-p, --print\t\t\tprint the page after all process\n\t\t\t\tthis is DEFAULT chosen\n");
	printf("-c, --count\t\t\tprint the appearance time of English characters, blanks, \n\t\t\t\tArabic numberals and all characters after all process\n\t\t\t\tthis will override '-p'\n");
	printf("-d, --delete <parameter>\tdelete a certain string\n");
	printf("-r, --remove <parameter>\tremove a line\n\t\t\t\twill ignore invalid lines\n");
	printf("-h, --help\t\t\tshow this page and exit\n");
	printf("-v, --version\t\t\tshow imformation of the program and exit\n");
	printf("\t--interactive\t\trun in interactive mode\n\t\t\t\tsame as using no parameters\n");
	printf("\ninvalid options will be IGNORED\n");
	printf("\n");
}
int parametric(int argc, char **argv) {
	char **page = NULL, line[81];
	int iarg = 0, lnum = 0, length, linenum;
	int cnum[4];
	BOOL flag = FALSE;
	if ((!strcmp(argv[1], "-h")) || (!strcmp(argv[1], "--help"))) {
		phelp(argc, argv);
		return 1;
	} else if ((!strcmp(argv[1], "-v")) || (!strcmp(argv[1], "--version"))) {
		show_version();
		return 1;
	}
	lnum = readpage(&page, lnum);
	while (++iarg < argc) {
		if (!(strcmp(argv[iarg], "-d") && strcmp(argv[iarg], "--delete"))) {
			++iarg;
			if (iarg < argc)
				del(page, lnum, argv[iarg]);
		} else {
			if (!(strcmp(argv[iarg], "-c") && strcmp(argv[iarg], "--count"))) {
				flag = TRUE;
			} else {
				if (!(strcmp(argv[iarg], "-r") && strcmp(argv[iarg], "--remove"))) {
					++iarg;
					if (iarg < argc) {
						linenum = atoi(argv[iarg]);
						removeline(&page, &lnum, linenum);
					}
				}
			}
		}
	}
	if (flag) {
		basic_count(page, lnum, cnum);
		print_count(cnum);
	} else {
		printf("%d\n", lnum);
		print_page(page, lnum);
	}
	clean(&page, &lnum);
	return 1;
}
void deal_error() {
	printf("ERROR\n");
}
void blank_page() {
	printf("You haven't written down a page yet!\n");
}
#endif
