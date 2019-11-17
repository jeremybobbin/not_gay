#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "calc.h"

int main(int argc, char *argv[]) {
	int type;
	double op2;
	char s[MAXOP];
	double r[26]; /* register */
	char lr; /* last register */

	for (int i = 0; i < 26; i++)
		r[i] = 0;

	while (++argv && --argc > 0 && (type = getop(s, *argv)) != '\0') {
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
			case '\0':
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
