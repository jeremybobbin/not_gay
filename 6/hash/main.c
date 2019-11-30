#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101

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
	struct nlist *el;
	for (int i = 0; i < HASHSIZE; i++)
		for (el = hashtab[i]; el != NULL; el = el->next)
			printf("%d. %s\n", i+1, el->name);
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


int main(int argc, char *argv[])
{
	for (int i = 0; i < HASHSIZE; i++)
		hashtab[i] = NULL;

	install("Blacks", "dang");
	install("Person", "Rocket");
	install("Guy", "Spice");
	install("Guy", "Marriage");

	hashprint();
	return 0;
}
