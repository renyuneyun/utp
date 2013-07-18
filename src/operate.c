/* operate.c */
#ifndef OPERATE
#define OPERATE
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
#include "operate.h"
int basic_count(char **pv, int pc, int *num) {
	int ec_u, ec_d, bc, nc, ac;
	char ch;
	int i, j;
	ec_u = ec_d = bc = nc = ac = 0;
	for (i = 0; i < pc; ++i) {
		j = 0;
		ch = pv[i][j];
		while ((ch != '\0') && (ch != '\n')) {
			if ((ch >= 'a') && (ch <= 'z'))
				++ec_d;
			else if ((ch >= 'A') && (ch <= 'Z'))
				++ec_u;
			else if ((ch >= '0') && (ch <= '9'))
				++nc;
			else if ((ch == ' ') || (ch == '\t'))
				++bc;
			++ac;
			ch = pv[i][++j];
		}
	}
	num[0] = ac;
	num[1] = ec_u + ec_d;
	num[2] = bc;
	num[3] = nc;
	return 1;
}
int count_string(char **pv, int pc, char *s) {
	int n = 0;
	char ss[81];
	int i;
	for (i = 0; i < pc; ++i) {
		strcpy(ss, pv[i]);
		n += delline(ss, s);
	}
	return n;
}
int delline(char *line, char *str) {
	int len, slen, n = 0;
	//char *p;
	long i, j;
	slen = strlen(str);
	len = strlen(line) + 1;
	while (((i = (strstr(line, str) - line)) >= 0) && (i <= len)) {
		for (j = i; j < len - slen; ++j) {
			line[j] = line[j + slen];
		}
		len -= slen;
		++n;
	}
	return n;
}
int del(char **page, int lnum, char *str) {
	int i, n = 0;
	for (i = 0; i < lnum; ++i) {
		n += delline(page[i], str);
	}
	return n;
}
#endif
