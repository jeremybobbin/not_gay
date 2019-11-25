#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, QUALIFIER };

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dirdcl(void);
void dcl(void);

int ch = -1;
int getch()
{
	char c = ch == -1 ? getchar() : ch;
	ch = -1;
	return c;
}

void ungetch(int c)
{
	ch = c;
}

void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; )
		ns++;

	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void)
{
	int type;
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			printf("error: missing ')' \n");
	} else if (tokentype == NAME)
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

int gettoken()
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t');

	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);

		if (strcmp(token, "static") == 0 ||
				strcmp(token, "const") == 0 ||
				strcmp(token, "extern") == 0 ||
				strcmp(token, "register") == 0)
			return tokentype = QUALIFIER;

		return tokentype = NAME;
	} else
		return tokentype = c;
}

int main(int argc, char *argv)
{
	char *t;
	while (gettoken() != EOF) {
		while (tokentype == QUALIFIER) {
			strcat(datatype, token);
			strcat(datatype, " ");
			gettoken();
		}
		strcat(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n') {
			printf("syntax error\n");
			while (getch() != '\n');
		}
		printf("%s: %s %s\n", name, out, datatype);
		datatype[0] = '\0';
	}
	return 0;
}
