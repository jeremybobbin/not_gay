#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 50

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
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

struct node *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

//char *strdup(char *s)
//{
//	char *p = (char *) malloc(strlen(s)+1);
//	if (p != NULL)
//		strcpy(p, s);
//	return p;
//}

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}

}

char *last = NULL;
int ncmp = 6;
void grouptreeprint(struct tnode *p)
{
	if (last == NULL)
		last = p->word;
	if (p != NULL) {
		grouptreeprint(p->left);


		printf("%s ", p->word);
		if (strncmp(p->word, last, ncmp))
		{
			putchar('\n');
			last = p->word;
		}

		grouptreeprint(p->right);
	}

}


int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	if (argc > 1)
		ncmp = atoi(argv[1]);

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	grouptreeprint(root);
	return 0;
}
