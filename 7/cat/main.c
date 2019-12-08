#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>


double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

int cat_by_char(FILE *ifp, FILE *ofp)
{
	int c;
	while ((c = fgetc(ifp)) != EOF)
		fputc(c, ofp);

}

int cat_by_buf(FILE* ifp, FILE* ofp)
{
	int n;
	char buf[BUFSIZ];
	while ((n = read(ifp, buf, BUFSIZ)) > 0)
		if (write(ofp, buf, n) != n)
			fprintf(stderr, "DANG. Error writing file\n");
}


#define MAX_ITER 1000

int main(int argc, char *argv[])
{
	double t;
	int i, j, c;
	FILE *iop;

	if (argc == 1) {
		while ((c = getchar()) != EOF)
			putchar(c);
		exit(0);
	}

	t = get_time();
	for (j = 0; j < MAX_ITER; j++)
		for (i = 1; i < argc; i++)
			if ((iop = fopen(argv[i], "r")) != NULL) {
				cat_by_char(iop, stderr);
				fclose(iop);
			} else
				fprintf(stderr, "%s: could not open file %s\n", argv[i]);

	printf("Cat by char: %lf\n", get_time() - t);

	t = get_time();
	for (j = 0; j < MAX_ITER; j++)
		for (i = 1; i < argc; i++)
			if ((iop = fopen(argv[i], "r")) != NULL) {
				cat_by_buf(iop, stderr);
				fclose(iop);
			} else
				fprintf(stderr, "%s: could not open file %s\n", argv[i]);

	printf("Cat by buf: %lf\n", get_time() - t);


	exit(0);
	
	//for (i = 0; i < MAX_ITER; i++)
	//	isupper_fn(i);

	//t = get_time();
	//for (i = 0; i < MAX_ITER; i++)
	//	isupper_macro(i);

	//printf("%lf\n", get_time() - t);

}

