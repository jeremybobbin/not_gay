#define MAXOP 100
#define NUMBER '0'
#define REGISTER '1'
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int strlen(char[]);
