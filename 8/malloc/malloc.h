typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

#define NEXT(x) ((x)->s.ptr)
#define SIZE(x) ((x)->s.size)
void *malloc(unsigned);

#define NALLOC 1024
static Header *morecore(unsigned);

void free(void *);
