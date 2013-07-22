/* operate.c */
#ifndef OPERATE
#define OPERATE
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
		n += delinline(ss, s);
	}
	return n;
}
int delinline(char *line, char *str) {
	int len, slen, n = 0;
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
		n += delinline(page[i], str);
	}
	return n;
}
int removeline(char ***page0, int *lnum0, int linenum) {
	char **page = *page0;
	int lnum = *lnum0;
	int i;
	if (!page) {
		return -1;
	}
	for (i = linenum; i < lnum; ++i) {
		page[i - 1] = page[i];
	}
	--lnum;
	page = (char **) realloc(page, sizeof(char *) * lnum);
	*lnum0 = lnum;
	*page0 = page;
	if (!page) {
		return 0;
	}
	return 1;
}
#endif
