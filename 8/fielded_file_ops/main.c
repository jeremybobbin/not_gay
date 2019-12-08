#include <sys/resource.h>
#include <sys/time.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <sys/fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include "fileops.h"

#define PERMS 0666

int _fillbuf(FILE *fp)
{
	int bufsize;
	if (!fp->read || fp->eof || fp->err)
		return EOF;

	bufsize = fp->unbuf ? 1 : BUFSIZ;
	if (fp->base == NULL) 	/* there is no buffer */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; /* can't alloc */

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->eof = 1;
		else
			fp->err = 1;

		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = {
	/* b          b           c  r  w  u  e  e  f */
	/* a          u           o  e  r  n  o  r  d */
	/* s          f           u  a  i  b  f  r    */
	/* e          p           n  d  t  u     o    */
	/*                        t     e  f     r    */
	{ 0, (char *) 0, (char *) 0, 1, 0, 0, 0, 0, 0 },
	{ 0, (char *) 0, (char *) 0, 0, 1, 0, 0, 0, 1 },
	{ 0, (char *) 0, (char *) 0, 0, 1, 1, 0, 0, 2 },
};

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (!fp->read && !fp->write)
			break;

	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);

	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->read = *mode == 'r';
	fp->write = *mode != 'r';
	return fp;
}

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

double cat_by_char(FILE *ifp)
{
	int c;
	double n;


	return n;
}

#define MAX_ITER 1000000
int main(int argc, char *argv[])
{
	int i, j, c, e;
	FILE *iop;
	double t;

	for (j = 0; j < MAX_ITER; j++)
		for (i = 1; i < argc; i++)
			if ((iop = fopen(argv[i], "r")) != NULL) {
				while ((c = getc(iop)) != EOF)
					if (write(1, &c, 1) != 1)
						return -1;
				if ((e = close(iop->fd)) != 0)
					return e;
				iop->read = 0;
				iop->write = 0;
				iop = NULL;
			} else exit(3);
	exit(0);
}

