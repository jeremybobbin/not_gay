#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>


#define MAX_ITER 1000000000
#define isupper_macro(a) a >= 'A' && a <= 'Z'

int isupper_fn(char a)
{
	return a >= 'A' && a <= 'Z';
}

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}


int main(int argc, char *argv[])
{
	double t;
	int i;
	
	t = get_time();
	for (i = 0; i < MAX_ITER; i++)
		isupper_fn(i);
	printf("%lf\n", get_time() - t);

	t = get_time();
	for (i = 0; i < MAX_ITER; i++)
		isupper_macro(i);

	printf("%lf\n", get_time() - t);

}

