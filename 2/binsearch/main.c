#include <stdio.h>
#include <time.h>

unsigned jbinsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (v[mid] == x)
		return mid;
	else
		return -1;
}

unsigned binsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x < v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main(int argc, char * argv) {
	int nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } ;
	clock_t begin;
	clock_t end;

	begin = clock();
	binsearch(0, nums, 16);
	end = clock();
	double book = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	jbinsearch(0, nums, 16);
	end = clock();
	double jer = (double)(end - begin) / CLOCKS_PER_SEC;


	printf("Jer: %f\tBook: %f\n", jer, book);
	return 0;
}
