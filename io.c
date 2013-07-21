/* io.c */
#ifndef IO
#define IO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "def.h"
int readcommand() {
	char command[MAXCOMMANDLENGTH];
	signed char ch;
	int len = -1;
	while ((ch = getchar()) > -1) {
		if (ch == '\n'){
			command[++len] = '\0';
			return dealcommand(command);
		}
		if (len > MAXCOMMANDLENGTH)
			break;
		command[++len] = ch;
	}
	return COM_ERROR;
}
int dealcommand(char *command) {
	if (!strcmp(command, "quit"))
		return COM_QUIT;
	if (!strcmp(command, ""))
		return COM_NULL;
	if (!strcmp(command, "help"))
		return COM_HELP;
	if (!strcmp(command, "version"))
		return COM_VERSION;
	if (!strcmp(command, "print"))
		return COM_PRINT;
	if (!strcmp(command, "new"))
		return COM_NEW;
	if (!strcmp(command, "delete"))
		return COM_DELETE;
	if (!strcmp(command, "count"))
		return COM_COUNT;
	if (!strcmp(command, "append"))
		return COM_APPEND;
	if (!strcmp(command, "search"))
		return COM_SEARCH;
	if (!strcmp(command, "remove"))
		return COM_REMOVE;
	return COM_ERROR;
}
int readnum() {
	int num;
	scanf("%d", &num);
	while (getchar() != '\n')
		;
	return num;
}
int readline(char line[]) {
	int num = 0;
	signed char ch;
	while (((ch = getchar()) > EOF) && (ch != '\n')) {
		if (ch == '\r')
			continue;
		line[num++] = (unsigned char) ch;
	}
	if (num == 0) {
		if (ch == EOF)
			return -1;
		return 0;
	}
	line[num] = '\0';
	return num;
}
int readpage(char ***page0, int lnum0) {
	char **page = *page0;
	int length = 0, lnum = lnum0;
	char line[81];
	int len = 0;
	int exitcontrol = 0;
	while (!page) {
		if ((len = readline(line)) > 0) {
			exitcontrol = 0;
			++lnum;
			length = len;
			page = (char **) malloc(sizeof(char *));
			if (!page) {
				mem_error();
			}
			page[lnum - 1] = (char *) malloc(sizeof(char) * (len + 1));
			if (!page[lnum - 1]) {
				mem_error();
			}
			strcpy(page[lnum - 1], line);
		}
		if (len == -1) {
			*page0 = page;
			return lnum;
		}
		if (len == 0) {
			++exitcontrol;
			if (exitcontrol == EXITTIMES) {
				*page0 = page;
				return lnum;
			}
			continue;
		}
	}
	while ((len = readline(line)) > -1) {
		if (len == 0) {
			++exitcontrol;
			if (exitcontrol == EXITTIMES) {
				*page0 = page;
				return lnum;
			}
			continue;
		}
		exitcontrol = 0;
		++lnum;
		length += len;
		page = (char **) realloc(page, sizeof(char *) * lnum);
		if (!page) {
			mem_error();
			return 0;
		}
		page[lnum - 1] = (char *) malloc(sizeof(char) * (len + 1));
		if (!page[lnum - 1]) {
			mem_error();
			return 0;
		}
		strcpy(page[lnum - 1], line);
	}
	*page0 = page;
	return lnum;
}
void print(int num[4], char **page, int lnum) {
	int i;
	for (i = 1; i < 4; ++i) {
		printf("%d ", num[i]);
	}
	printf("%d\n", num[0]);
	for (i = 0; i < lnum; ++i) {
		printf("%s\n", page[i]);
	}
}
void print_count(int num[4]) {
	printf("English characters: %d\n", num[1]);
	printf("Blanks: %d\n", num[2]);
	printf("Arabic numerals: %d\n", num[3]);
	printf("All characters: %d\n", num[0]);
}
void print_page(char **page, int lnum) {
	int i;
	if (page == NULL)
		return;
	for (i = 0; i < lnum; ++i) {
		printf("%s\n", page[i]);
	}
}
void mem_error() {
	printf("Sorry, no enough memory space.\n");
}
void clean(char ***page0, int *lnum0) {
	char **page= *page0;
	int lnum = *lnum0;
	int i;
	if (page) {
		for (i = 0; i < lnum; ++i) {
			free(page[i]);
		}
		free(page);
	}
	*page0 = NULL;
	*lnum0 = 0;
}
#endif
