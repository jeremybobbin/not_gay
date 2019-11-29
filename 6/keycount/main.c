#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NKEYS 50

char *keyword[NKEYS];
int keycount[NKEYS];

char *word;
int count;

struct key {
	char *word;
	int count;
} keytab[NKEYS] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0,
};


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



enum { NONE = 0, STRING, CHAR_STRING, COMMENT, LINE_COMMENT, PREPROC };
int state = 0;
int escaped = 0;
/* getch ignorignoring comments, string literals, preprocessor directives */

#define MAX(a, b) a > b ? a : b
int getchgood()
{
	int c, getch(void);
	void ungetch(int);

	for (;;) {
		if ((c = getch()) == EOF)
			return c;
		
		if (escaped > 0)
			escaped--;

		if (c == '\\')
			if (escaped)
				escaped = 0;
			else
				escaped = 2;

		char *w, *e;
		switch (state) 
		{
			case NONE:
				w = "NONE";
				break;
			case STRING:
				w = "STRING";
				break;
			case CHAR_STRING:
				w = "CHAR_STRING";
				break;
			case COMMENT:
				w = "COMMENT";
				break;
			case LINE_COMMENT:
				w = "LINE_COMMENT";
				break;
			case PREPROC:
				w = "PREPROC";
				break;
		}
		if (escaped)
			e = "TRUE";
		else
			e = "FALSE";
		//printf("CHAR: '%c', STATE: %s, ESCAPED: %s \n", c, w, e);

		if (state == LINE_COMMENT || state == PREPROC) {
			if (c == '\n' && !escaped)
				state = NONE;
		} else if (state == COMMENT && c == '*') {
			if ((c = getch()) == '/')
				state = NONE;
			else {
				ungetch(c);
				return '*';
			}
		} else if (state == STRING) {
			if (c == '"' && !escaped)
				state = NONE;
		} else if (state == CHAR_STRING) {
			if (c == '\'' && !escaped)
				state = NONE;
		} else if (state == NONE) {
			if (c == '/') // "/*"
				if ((c = getch()) == '*')
					state = COMMENT;
				else if (c == '/')
					state = LINE_COMMENT;
				else {
					ungetch(c);
					return '/';
				}
			else if (c == '"')
				state = STRING;
			else if (c == '\'')
				state = CHAR_STRING;
			else if (c == '#')
				state = PREPROC;
			else
				return c;
		}
	}
}

int chgood = -1;
void ungetchgood(int c)
{
	chgood = c;
}

int getword(char *word, int lim)
{
	int c, getchgood(void);
	void ungetchgood(int);
	char *w = word;

	while (isspace(c = getchgood()));
	if (c != EOF)
		*w++ = c;

	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for ( ; --lim > 0; w++)
		if (!(isalnum(*w = getch()) || *w == '_')) {
			ungetchgood(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int main(int argc, char *argv)
{
	char c;
	while ((c = getchgood()) != EOF)
		putchar(c);

	return 0;
}
