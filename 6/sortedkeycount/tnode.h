struct tree {
	struct node *head;
	int count;
	int (*compare)(void *, void *)
};

struct node {
	struct node *left;
	struct node *right;
	void *data;
};

struct node *node_alloc(void);

void add(struct tree *, void *);
void *rm(struct tree *, void *);
void *find(struct tree *, void *);
