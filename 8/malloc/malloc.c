#include <unistd.h>
#include "malloc.h"

static Header base;
static Header *freep = NULL;

void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;

	if (nbytes < 1) /* sanity check */
		return NULL;

	/* Space we need in terms of "Headers"
	 * 	For example: malloc(16);
	 *
	 * 	nbytes == 16;
	 * 	sizeof(Header) == 16;
	 *
	 * 	(nbytes+sizeof(Header)-1) == 31
	 * 	(31 / 16) + 1 == 2;
	 *
	 * 	We then make space for 32 bytes
	 * 	OR
	 * 	2 headers
	 *
	 */
	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1; 

	if ((prevp = freep) == NULL) {
		NEXT(base) = freep = prevp = &base;
		SIZE(base) = 0;
	}

	for (p = NEXT(prevp); ; prevp = p, p = NEXT(p)) {
		if (SIZE(p) >= nunits) {
			if (SIZE(p) == nunits)
				NEXT(prevp) = NEXT(p);
			else {
				/*
				 * 	Example:
				 * 	nunits = 5
				 * 	SIZE(p) = 9
				 *	P: p________n
				 *
				 * 	SIZE(p) -= 5;
				 * 	p += 4;
				 *
				 *	P: p___p____
				 *	SIZE(p) = 5
				 *
				 *	Sizes  : 4___5____
				 *	Return : _____R___
				 */
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

	/*
	 * 	bp > p && bp < NEXT(p)
	 * 	When bp is in between p and n
	 *
	 *
	 */
	for (p = freep; !(bp > p && bp < NEXT(p)); p = NEXT(p))
		/*	p >= NEXT(p) && bp > NEXT(p)
		 *	n________p___b___
		 *
		 *	p >= NEXT(p) && bp < p
		 *	b__n__________p__
		 *
		 */
		if (p >= NEXT(p) && (bp < p || bp > NEXT(p)))
			break;


	if (bp + SIZE(bp) == NEXT(p)) {
		if ((SIZE(NEXT(p))) < 1)
			return;
		SIZE(bp) =+ SIZE(NEXT(p));
		NEXT(bp) = NEXT(NEXT(p));
	} else
		NEXT(bp) = NEXT(p);

	if (p + SIZE(p) == bp) {
		if (SIZE(bp) < 1)
			return;
		SIZE(p) =+ SIZE(bp);
		NEXT(p) = NEXT(bp);
	} else
		NEXT(p) = bp;

	freep = p;
}

void *bfree(void *p, unsigned n)
{
	Header *bp;

	bp = (Header *)ap - 1;

	SIZE(bp) = ALIGN(n);

	if ((prevp = freep) == NULL) {
		NEXT(base) = freep = &base;
		SIZE(base) = 0;
	}

	free(bp+1);
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
