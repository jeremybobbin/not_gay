#include <unistd.h>
#include "malloc.h"

static Header base;
static Header *freep = NULL;

void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;
	nunits = (nbytes+sizeof(Header)-1) / sizeof(Header)+1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = NEXT(prevp); ; prevp = p, p = NEXT(p)) {
		if (SIZE(p) >= nunits) {
			if (SIZE(p) == nunits)
				NEXT(prevp) = NEXT(p);
			else {
				SIZE(p) -= nunits;
				p += SIZE(p);
				SIZE(p) = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)
		{

			if ((p = morecore(nunits)) == NULL)
			{
				return NULL;
			}
		}
	}
}

void *calloc(int n, unsigned nbytes)
{
	char *head;
	int size = n*nbytes;
	if ((head = malloc(size)) == NULL)
		return NULL;

	while (--size)
		*(head+size) = 0;

	return (void *)head;
}

void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p && bp < NEXT(p)); p = NEXT(p))
		if (p >= NEXT(p) && (bp < p || bp > NEXT(p)))
			break;

	if (bp + SIZE(bp) == NEXT(p)) {
		SIZE(bp) =+ SIZE(NEXT(p));
		NEXT(bp) = NEXT(NEXT(p));
	} else
		NEXT(bp) = NEXT(p);

	if (p + SIZE(p) == bp) {
		SIZE(p) =+ SIZE(bp);
		NEXT(bp) = NEXT(bp);
	} else
		NEXT(p) = bp;

	freep = p;
}

static Header *morecore(unsigned nu)
{
	char *cp;
	//void *sbrk(intptr_t); /* raeee */
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;


	cp = sbrk(nu*sizeof(Header));
	if (cp == (char *) -1)
		return NULL;

	up = (Header *) cp;
	SIZE(up) = nu;
	free((void *)(up+1));
	return freep;
}
