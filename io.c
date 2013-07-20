/* io.c */
#ifndef IO
#define IO
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif
#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif
#include "io.h"
#include "def.h"
int readcommand(void) {
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
		line[num++] = (unsigned char) ch;
	}
	if (num == 0)
		return 0;
	line[num] = '\0';
	return num;
}
int readpage(char ***page0, int lnum0) {
	char **page = *page0;
	int length = 0, lnum = lnum0;
	char line[81];
	int len = 0;
	if (!page) {
		if ((len = readline(line)) > 0) {
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
	}
	while ((len = readline(line)) > 0) {
		++lnum;
		length += len;
		page = (char **) realloc(page, sizeof(char *) * lnum);
		if (!page) {
			mem_error();
			return;
		}
		page[lnum - 1] = (char *) malloc(sizeof(char) * (len + 1));
		if (!page[lnum - 1]) {
			mem_error();
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
void mem_error(void) {
	printf("Sorry, no enough memory space.\n");
}
void deal_error(void) {
	printf("ERROR\n");
}
void blank_page(void) {
	printf("You haven't written down a page yet.\n");
}
void clean(char **page, int lnum) {
	int i;
	if (page) {
		for (i = 0; i < lnum; ++i) {
			free(page[i]);
		}
		free(page);
	}
}
#endif
