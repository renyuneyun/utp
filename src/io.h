extern int readline(char line[]);
extern int readpage(char ***page0, int *lnum0, int *length0);
extern void print(int num[4], char **page, int lnum);
extern void print_count(int num[4]);
extern void print_page(char **page, int lnum);
extern void deal_error(void);
extern void clean(char **page, int lnum);
