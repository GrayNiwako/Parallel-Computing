#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void Count_sort(int a[], int n) {
	int i, j, count;
	int* temp = malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		count = 0;
		for (j = 0; j < n; j++)
			if (a[j] < a[i])
				count ++;
			else if (a[j] == a[i] && j < i)
				count ++;
		temp[count] = a[i];
	}

	memcpy(a, temp, n * sizeof(int));
	free(temp);
}

#define n 10000

int main(int argc, char* argv[]) {
	int a[n], i;
	struct timeval start;
	struct timeval end;
	unsigned long diff;

	for (i = 0; i < n; i ++)
		a[i] = n - i;

// no parallel
	gettimeofday(&start, NULL);
	Count_sort(a, n);
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;	

	printf("no parallel, time = %ld microseconds\n", diff);
	//for (i = 0; i < n; i ++)
	//	printf("%d ", a[i]);
	//printf("\n");
	return 0;
}
