#ifndef DEC_H
#define DEC_H
extern int readcommand();
extern int readline(char *);
extern int readpage(char ***page0, int lnum0);
extern void print_count(int num[4]);
extern void print_page(char **page, int lnum);
extern void deal_error(void);
extern void clean(char **page, int lnum);
extern int basic_count(char **pv, int pc, int *num);
extern int count_string(char **pv, int pc, char *s);
extern int del(char **page, int lnum, char *str);
#endif
