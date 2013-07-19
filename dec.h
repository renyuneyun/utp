#ifndef DEC_H
#define DEC_H
int readcommand();
int readline(char *);
int readpage(char ***page0, int lnum0);
void print_count(int num[4]);
void print_page(char **page, int lnum);
void deal_error(void);
void clean(char **page, int lnum);
int basic_count(char **pv, int pc, int *num);
int count_string(char **pv, int pc, char *s);
int del(char **page, int lnum, char *str);
#endif
