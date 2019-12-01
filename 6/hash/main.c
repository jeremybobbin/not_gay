#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAX_WORD 50
#define MAX_DEFN 500

static struct nlist *hashtab[HASHSIZE];

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};


unsigned hash(char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free ((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

void hashprint() {
	for (int i = 0; i < HASHSIZE; i++)
		for (struct nlist *el = hashtab[i]; el != NULL; el = el->next)
			printf("%d. %s\n", i+1, el->name);
}

int undef(char *s) {
	struct nlist *np; /* nlist pointer */ 
	struct nlist *nnp; /* nlist pointer */ 
	struct nlist **pp; /* previous pointer */ 
	unsigned h;

	/*
	 * For whatever reason, the following doesn't work:
	 * for (np = hashtab[hash(s)], pp = &np; np != NULL; pp = &np->next, np = np->next)
	 *                             ^^^^^^^^
	 *                               pp is NOT set to &hashtab[hash(s)]
	 *                               pretty gay...
	 *
	 */

	for (np = *(pp = &hashtab[hash(s)]); np != NULL; pp = &np->next, np = np->next)
		if (strcmp(s, np->name) == 0)
			break;

	*pp = np->next;
}

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

int chgood = -1;
void ungetchgood(int c)
{
	chgood = c;
}

/* getch ignorignoring comments, string literals, preprocessor directives */
#define MAX(a, b) a > b ? a : b

int goodbuf = -1;
int getchgood()
{
	int c, getch(void);
	void ungetch(int);
	if (goodbuf != -1) {
		c = goodbuf;
		goodbuf = -1;
		return c;
	}

	if (chgood != -1) {
		c = chgood;
		chgood = -1;
		return c;
	}

	if ((c = getch()) == EOF)
		return c;

	if (escaped > 0)
		escaped--;

	if (c == '\\')
		if (escaped)
			escaped = 0;
		else
			escaped = 2;

	if (state == LINE_COMMENT || state == PREPROC) {
		if (c == '\n' && !escaped)
			state = NONE;
	} else if (state == COMMENT && c == '*') {
		if ((c = getch()) == '/') {
			goodbuf = c;
			return '*';
			state = NONE;
		}
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
			if ((c = getch()) == '*') {
				goodbuf = c;
				state = COMMENT;
				return '/';
			} else if (c == '/') {
				goodbuf = c;
				state = LINE_COMMENT;
				return '/';
			}
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
	}

	return c;
}


int getword(char *word, int lim)
{
	int c, getchgood(void);
	void ungetchgood(int);
	char *w = word;

	if ((c = getchgood()) == EOF)
		return 0;

	if (isalpha(*w++ = c))
		for ( ; --lim > 0; w++)
			if (!(isalnum(*w = getch()) || *w == '_')) {
				ungetchgood(*w);
				break;
			}

	*w = '\0';
	return w - word;
}

int instdefn() {
	char k[MAX_WORD], v[MAX_DEFN], word[MAX_WORD];
	v[0] = '\0';
	int len;

	getword(k, MAX_WORD); /* skip white spaces */
	getword(k, MAX_WORD); /* skip white spaces */
	getword(v, MAX_WORD); /* skip white spaces */

	while (getword(word, MAX_WORD) != 0 && state == PREPROC) {
		printf("%s", word);
		strcat(v, word);
	}

	install(k, v);
}


int main(int argc, char *argv[])
{
	char c, word[MAX_WORD];
	struct nlist *np;
	int len;

	for (int i = 0; i < HASHSIZE; i++)
		hashtab[i] = NULL;



	while ((len = getword(word, MAX_WORD)) != 0) {
		if (len == 1)
			putchar(word[0]);
		else if (strcmp(word, "define") == 0 && state == PREPROC) {
			printf("%s", word);
			instdefn();
		} else if (np = lookup(word)) {
			printf("%s", np->defn);
		} else 
			printf("%s", word);
	}
	return 0;
}
