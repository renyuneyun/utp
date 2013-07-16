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
int readline(char line[]) {
	int num = 0;
	signed char ch;
	while (((ch = getchar()) > 0) && (ch != '\n')) {
		line[num++] = (unsigned char) ch;
	}
	if (num == 0)
		return 0;
	line[num] = '\0';
	return num - 1;
}
int readpage(char ***page0, int *lnum0, int *length0) {
	char **page;
	int length = 0, lnum = 0;
	char line[81];
	int len = 0;
	if ((len = readline(line)) > 0) {
		++lnum;
		length = len;
		page = (char **) malloc(sizeof(char *));
		if (!page) {
			deal_error();
		}
		page[lnum - 1] = (char *) malloc(sizeof(char) * (len + 1));
		if (!page[lnum - 1]) {
			deal_error();
		}
		strcpy(page[lnum - 1], line);
	}
	while ((len = readline(line)) > 0) {
		++lnum;
		length += len;
		page = (char **) realloc(page, sizeof(char *) * lnum);
		if (!page) {
			deal_error();
			return;
		}
		page[lnum - 1] = (char *) malloc(sizeof(char) * (len + 1));
		if (!page[lnum - 1]) {
			deal_error();
		}
		strcpy(page[lnum - 1], line);
	}
	*page0 = page;
	*lnum0 = lnum;
	*length0 = length;
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
extern void print_count(int num[4]) {
	int i;
	for (i = 1; i < 4; ++i) {
		printf("%d ", num[i]);
	}
	printf("%d\n", num[0]);
}
extern void print_page(char **page, int lnum) {
	int i;
	for (i = 0; i < lnum; ++i) {
		printf("%s\n", page[i]);
	}
}
void deal_error(void) {
	puts("ERROR\n");
}
void clean(char **page, int lnum) {
	int i;
	for (i = 0; i < lnum; ++i) {
		free(page[i]);
	}
	free(page);
}
#endif
