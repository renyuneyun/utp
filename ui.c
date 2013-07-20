/* ui.c */
#ifndef UI
#define UI
#define STDIO_H
#include <stdio.h>
#include "ui.h"
#include "dec.h"
#include "def.h"

void show_welcome(void) {
	printf("Welcome to use the Ugly Text Processor!\n");
	printf("Type 'help' to view a list of commands.\n");
}
void show_version(void) {
	printf("an Ugly Text Processor\n");
	printf("Verson: 0.11\n");
	printf("\nReport bugs or give advice to renyuneyun@gmail.com\n");
	printf("Have a good day:P\n");
}
void ihelp(void) {
	printf("possible commands are:\n");
	printf(BLANK"new\t\t\tstart a new page\n");
	printf(BLANK"append\t\t\tappend some parameters to the existing page\n");
	printf(BLANK"print\t\t\tprint the current page\n");
	printf(BLANK"count\t\t\tprint the number of English characters, blank, \n\t\t\tArabic numerals, and all characters\n");
	printf(BLANK"search\t\t\tshow how many times a string appears\n");
	printf(BLANK"delete\t\t\tdelete one certain string in the page\n");
	printf(BLANK"remove\t\t\tremove one line\n");
	printf(BLANK"help\t\t\tshow this page\n");
	printf(BLANK"version\t\t\tshow the version information\n");
	printf(BLANK"quit\t\t\tquit the program\n");
}
int interactive(void) {
	char **page = NULL, line[81];
	int icommand, lnum = 0, length, itimes, linenum;
	int cnum[4];
	show_welcome();
	while ((printf("(ute)")) && (icommand = readcommand())) {
		switch (icommand) {
			case COM_NULL :
				break;
			case COM_ERROR :
				printf("Unknown Command!\n");
				ihelp();
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
				printf("type your page below:(use \"Ctrl + D\" to finish typing)\n");
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
					if (readline(line))
						del(page, lnum, line);
					else
						deal_error();
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
				printf("type what you want to add below: (use \"Ctrl + D\" to finish typing)\n");
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
	clean(page, lnum);
	return 1;
}
void phelp(int argc, char **argv) {
	printf("Ugly Text Editor\n");
	printf("If you want to use the interactive mode, start the program with NO parameters\n");
	printf("Usage:\n");
	printf("%s [-option] [-s <string>] [-d <string>]\n", argv[0]);
	printf("-c, --count\t\t\tprint the appearance time of English characters, blanks, Arabic numberals and all characters after all process\n");
	//printf("-s, --search <parameter>\t\tshow how many times a string appears\n");
	printf("-d, --delete <parameter>\t\tdelete a certain string\n");
	printf("-r, --remove <parameter>\t\tremove a line\n\t\t\t\tignore invalid lines\n");
	printf("-h, --help\t\tshow this page and exit\n");
	printf("-v, --version\t\tshow imformation of the program and exit\n");
	printf("\t--interactive\t\trun in interactive mode\n\t\t\t\tsame as using no parameters\n");
	printf("\n");
}
int parametric(int argc, char **argv) {
	char **page = NULL, line[81];
	int iarg = 1, lnum = 0, length, linenum;
	int cnum[4];
	BOOL flag = FALSE;
	if ((!strcmp(argv[1], "-h")) || (!strcmp(argv[1], "--help"))) {
		phelp(argc, argv);
		return 1;
	} else if ((!strcmp(argv[1], "-v")) || (!strcmp(argv[1], "--version"))) {
		show_version();
		return 1;
	} else if ((argc & 1)) {
		deal_error();
		return 1;
	}
	lnum = readpage(&page, lnum);
	basic_count(page, lnum, cnum);
	--argc;
	while (iarg < argc) {
		if (!strcmp(argv[iarg], "-d")) {
			del(page, lnum, argv[iarg + 1]);
			basic_count(page, lnum, cnum);
			print_count(cnum);
			print_page(page, lnum);
		} else {
			if (!strcmp(argv[iarg], "-c")) {
				flag = TRUE;
			} else {
			/*if (!strcmp(argv[iarg], "-s")) {
				printf("The string \"%s\" appears %d times\n", argv[iarg + 1], count_string(page, lnum, argv[iarg + 1]));
			} else {*/
				if (!strcmp(argv[iarg], "-r")) {
					linenum = atoi(argv[iarg + 1]);
					removeline(&page, &lnum, linenum);
				}
			}
		}
		iarg += 2;
	}
	if (flag) {
		print_count(cnum);
	} else {
		print_page(page, lnum);
	}
	clean(page, lnum);
	return 1;
}
#endif
