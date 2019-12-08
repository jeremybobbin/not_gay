//#define NULL		0
#define EOF		(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20

typedef struct _iobuf {
	int  cnt;	/* characters left */
	char *ptr;	/* next character position */
	char *base;	/* location of buffer */
	int  read;	/* >>> modes of file access */
	int  write;
	int  unbuf;
	int  eof;
	int  err;	/* <<< modes of file access */
	int  fd;	/* file descriptor*/
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin	0
#define stdout	1
#define stderr	2

int _fillbuf(FILE *);
//int _flushbuf(int, FILE *);

#define feof(p) ((p)->eof)
#define ferror(p) ((p)->err)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
			       ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 \
			       ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdin)
