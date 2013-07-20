#ifndef IO_H
#define IO_H
int readcommand(void);
int dealcommand(char *command);
int readnum();
int readline(char line[]);
int readpage(char ***page0, int lnum0);
void print(int num[4], char **page, int lnum);
void print_count(int num[4]);
void print_page(char **page, int lnum);
void mem_error(void);
void deal_error(void);
void clean(char **page, int lnum);
#endif
