#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "calc.h"

int main(int argc, char * argv) {
	int type, ret;
	double op1, op2;
	char op;
	char opstring[MAXOP], *s;
	double r[26]; /* register */
	char lr; /* last register */

	for (int i = 0; i < 26; i++)
		r[i] = 0;

	while (scanf("%s", opstring) != EOF){
		if (sscanf(opstring, "%lf", &op1) == 1)
			push(op1);
		else
			for (s = opstring; op = *s; s++) {
				switch (op) {
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
						 /* results in actual value of the selected register
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
						if (op >= 'A' && op <= 'Z') {
							lr = op - 'A';
							push(r[lr]);
							break;
						}
						printf("error: unknown command %c\n", op);
						break;
				}
			}
	}
	return 0;
}


int strrev(char s[]) 
{
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
	return 0;
}


