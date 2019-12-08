#include <sys/resource.h>
#include <sys/time.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <sys/fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include "fileops.h"

#define PERMS 0666

int _fillbuf(FILE *fp)
{
	int bufsize;
	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) 	/* there is no buffer */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; /* can't alloc */

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;

		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
	int bufsize, written;
	char *end;
	int i;
	if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
		return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if  (bufsize > 1)
	{
		if (fp->base == NULL) /* there is no buffer */ {
			if ((fp->base =  (char *) malloc(bufsize)) == NULL)
				return EOF; /* can't alloc */

			fp->ptr = fp->base;
			fp->cnt = bufsize;
		}

		if (fp->ptr > fp->base) {
			end = fp->ptr;
			fp->ptr = fp->base;

			while (fp->ptr < end)
				fp->ptr += write(fp->fd, fp->ptr, end - fp->ptr);

			fp->cnt = bufsize;
			fp->ptr = fp->base;
		}
	}

	if (c != -1)
		if (write(fp->fd, &c, 1) != 1)
			return -1;


	return 0;
}

int fflush(FILE *fp) {
	return _flushbuf(-1, fp);
}

int fclose(FILE *fp) {
	int ret;
	if (ret = fflush(fp)) 
		return ret; /* return if non-zero*/
	fp->flag = 0;
	return 0;
}

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, _READ,          0 },
	{ 0, (char *) 0, (char *) 0, _WRITE,         1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 },
};

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

int fseek(FILE *fp, long offset, int whence) {
	int pos, bufsize;

	if (fp->flag & _READ)
		fp->cnt = 0;
	else if (fp->flag & _WRITE)
		fflush(fp);

	return lseek(fp->fd, offset, whence);
}

double get_time()
{
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec*1e-6;
}

int catn(FILE *ifp, FILE *ofp, int n)
{
	int c;
	while ((c = getc(ifp)) != EOF && n--)
		putc(c, ofp);
}

//#define MAX_ITER 1000
int main(int argc, char *argv[])
{
	int i;
	FILE *fp, *ofp;
	for (i = 1; i < argc; i++)
		if ((fp = fopen(argv[i], "r")) != NULL) {
			catn(fp, &_iob[stdout], 5);
			fseek(fp, -5, 2);
			catn(fp, &_iob[stdout], 100000);
			fclose(&_iob[stdout]);
		}
		else exit(1);

	return 0;


}


