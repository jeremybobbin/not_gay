#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#define MAXOP 100
#define NUMBER '0'
#define REGISTER '1'
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int main(int argc, char * argv) {
	int type;
	double op2;
	char s[MAXOP];
	double r[26]; /* register */
	char lr; /* last register */

	for (int i = 0; i < 26; i++)
		r[i] = 0;

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push((int) pop() % (int) op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				break;
			case 'p':
				printf("\t%.8g\n", r['P'] = pop());
				break;
			case 's':
				push(sin(pop()));
				break;
			case 'c':
				push(cos(pop()));
				break;
			case '^':
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case 'e':
				push(exp(pop()));
				break;
			case 'r': /* register */
				pop(); /* results in actual value of the selected register
					  we can ignore because 'lr' has what we want.
				*/
				r[(int) lr] = pop();
				break;
			case 'd':
				op2 = pop();
				push(op2);
				push(op2);
				break;
			default:
				if (type >= 'A' && type <= 'Z') {
					lr = type - 'A';
					push(r[lr]);
					break;
				}
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop() {
	if (sp > 0) {
		return val[--sp];
	}
	else {  
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')
		return c;


	i = 0;
	if (c == '-' && !isdigit(s[++i] = c = getch())) {
		ungetch(s[i--]);
		return '-';
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));

	if (c == '.')
		while (isdigit(s[++i] = c = getch()));

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

char buf[BUFSIZE];
int bufp = 0;
char eofs[BUFSIZE]; /* EOF offsets; stack of offsets */
int eofsp; /* EOF pointer */

int getch(void)
{
	if (eofs[eofsp]-- == 0) {
		eofsp--;
		return EOF;
	}

	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else if (c == EOF)
		eofs[++eofsp] = 0;
	else {
		eofs[eofsp]++;
		buf[bufp++] = c;
	}
}

void ungets(char s[]) {
	char c;
	int i;
	for (c = s[i = 0]; c != '\0'; c = s[i++])
		ungetch(s[i]);
}
