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
	struct occurance *occurances;
};

struct occurance {
	int lineno;
	struct occurance *next;
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


struct occurance *oalloc(int lineno)
{
	struct occurance *occ = malloc(sizeof(struct occurance));

	occ->next = NULL;
	occ->lineno = lineno;

	return occ;
}

void addocc(struct occurance* occ, int n) {
	if (occ->next == NULL) {
		occ->next = oalloc(n);
	} else
		addocc(occ->next, n);
}

int getword(char *word, int lim)
	
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while ((c = getch()) == '\t' || c == ' ' || c == '\r');
	if (c != EOF)
		*w++ = c;

	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for ( ; --lim > 0; w++)
		if (!(isalnum(*w = getch()) || *w == '_')) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

struct node *talloc(void)
{
	struct tnode *n = malloc(sizeof(struct tnode));
	n->occurances = NULL;
	return n;
}

struct tnode *addtree(struct tnode *p, char *w, int lineno)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
		p->occurances = oalloc(lineno);
	} else if ((cond = strcmp(w, p->word)) == 0) {
		p->count++;
		addocc(p->occurances, lineno);
	}
	else if (cond < 0)
		p->left = addtree(p->left, w, lineno);
	else
		p->right = addtree(p->right, w, lineno);
	return p;
}

int addnode(struct tnode *root, struct tnode *new) {
	if (new == NULL)
		return 1;
	int cond;

	printf("Adding\n");
	printf("Adding '%s' to '%s'\n", root->word, new->word);

	if (new->left != NULL) {
		addnode(new->left, new);
		new->left = NULL;
	}

	if (new->right != NULL) {
		addnode(new->right, new);
		new->right = NULL;
	}


	if ((cond = strcmp(root->word, new->word)) == 0)
	{
		printf("Error, '%s' already exists in tree.", root->word);
		return -1;
	} else if (cond < 0)
		if (root->left == NULL) {
			root->left = new;
		}
		else
			addnode(root->left, new);
	else
		if (root->right == NULL)
			root->right = new;
		else
			addnode(root->right, new);
}

removenode(struct tnode *root, struct tnode *del) {
	int cond;
	if ((cond = strcmp(root->word, del->word)) > 0 && root->left != NULL) {
		if (strcmp(root->left->word, del->word) == 0) {
			struct tnode *l = del->left;
			struct tnode *r = del->right;
			root->left = NULL;
			addnode(root, l);
			addnode(root, r);
		} else
			removenode(root->left, del);
	} else if (cond < 0 && root->right != NULL) {
		if (strcmp(root->right->word, del->word) == 0) {
			struct tnode *l = del->left;
			struct tnode *r = del->right;
			root->right = NULL;
			addnode(root, l);
			addnode(root, r);
		} else
			removenode(root->right, del);
	} else 
		printf("Trying to remove node that doesn't exist: '%s'.\n", del->word);
}

void occprint(struct occurance* occ) {
	if (occ != NULL) {
		printf(" %d", occ->lineno);
		occprint(occ->next);
	}
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%s", p->word);
		occprint(p->occurances);
		putchar('\n');
		treeprint(p->right);
	}

}


int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	char c;
	int lineno = 1;

	root = NULL;
	while ((c = getword(word, MAXWORD)) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word, lineno);
		else if (c == '\n')
			lineno++;

	struct tnode *remove = talloc();
	remove->word = "int";
	removenode(root, remove);

	remove->word = "printf";
	removenode(root, remove);

	remove->word = "char";
	removenode(root, remove);

	treeprint(root);
	return 0;
}
