#ifndef OPERATE_H
#define OPERATE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int basic_count(char **pv, int pc, int *num);
int count_string(char **pv, int pc, char *s);
int delinline(char *line, char *str);
int del(char **page, int lnum, char *str);
int removeline(char ***page0, int *lnum0, int linenum);
#endif
