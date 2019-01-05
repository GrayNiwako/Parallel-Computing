#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#define max 8
#define n 10000

int parallel_count[max];

int main(int argc, char* argv[]) {
	int a[n], i, j;
	struct timeval start;
	struct timeval end;
	unsigned long diff;
	// int thread_count = strtol(argv[1], NULL, 10);
	int thread_count = 4;
	int my_rank;
	int* temp = malloc(n * sizeof(int));

	for (i = 0; i < n; i ++)
		a[i] = n - i;

// parallel
	for (i = 0; i < max; i ++)
		parallel_count[i] = 0;

	gettimeofday(&start, NULL);

#	pragma omp parallel for num_threads(thread_count) \
		schedule(static)

	for (i = 0; i < n; i++) {
		my_rank = omp_get_thread_num();
		parallel_count[my_rank] = 0;
		for (j = 0; j < n; j++)
			if (a[j] < a[i])
				parallel_count[my_rank] ++;
			else if (a[j] == a[i] && j < i)
				parallel_count[my_rank] ++;
		temp[parallel_count[my_rank]] = a[i];
	}

	memcpy(a, temp, n * sizeof(int));
	free(temp);

	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;	

	printf("parallel, time = %ld microseconds\n", diff);
	//for (i = 0; i < n; i ++)
	//	printf("%d ", a[i]);
	//printf("\n");
	return 0;
}
