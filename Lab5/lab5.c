#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define max_x 8
#define n 100

int a[max_x][2];

void init() {
	int i, j;
	for (i = 0; i < max_x; i ++) {
		for (j = 0; j < 2; j ++)
			a[i][j] = -1;
	}
}

void output() {
	int i;
	for (i = 0; i < max_x; i ++) {
		if (a[i][0] != -1)
			printf("Thread %d: Iterations %d--%d\n", i, a[i][0], a[i][0] + a[i][1]);
	}
}

int main(int argc, char* argv[]) {
   	int thread_count = strtol(argv[1], NULL, 10);
	int my_rank, i;
	
// type = static
	init();
#	pragma omp parallel for num_threads(thread_count) \
		schedule(static)
	for (i = 0; i < n; i ++) {
		my_rank = omp_get_thread_num();
		if (a[my_rank][0] == -1) {
			a[my_rank][0] = i;
			a[my_rank][1] = 0;
		}
		else
			a[my_rank][1]++;
	}
	printf("static:\n");
	output();

// type = dynamic
	init();
#	pragma omp parallel for num_threads(thread_count) \
		schedule(dynamic)
	for (i = 0; i < n; i ++) {
		my_rank = omp_get_thread_num();
		if (a[my_rank][0] == -1) {
			a[my_rank][0] = i;
			a[my_rank][1] = 0;
		}
		else
			a[my_rank][1]++;
	}
	printf("dynamic:\n");
	output();

// type = guided
	init();
#	pragma omp parallel for num_threads(thread_count) \
		schedule(guided)
	for (i = 0; i < n; i ++) {
		my_rank = omp_get_thread_num();
		if (a[my_rank][0] == -1) {
			a[my_rank][0] = i;
			a[my_rank][1] = 0;
		}
		else
			a[my_rank][1]++;
	}
	printf("guided:\n");
	output();

// type = auto
	init();
#	pragma omp parallel for num_threads(thread_count) \
		schedule(auto)
	for (i = 0; i < n; i ++) {
		my_rank = omp_get_thread_num();
		if (a[my_rank][0] == -1) {
			a[my_rank][0] = i;
			a[my_rank][1] = 0;
		}
		else
			a[my_rank][1]++;
	}
	printf("auto:\n");
	output();

// type = runtime
	init();
#	pragma omp parallel for num_threads(thread_count) \
		schedule(runtime)
	for (i = 0; i < n; i ++) {
		my_rank = omp_get_thread_num();
		if (a[my_rank][0] == -1) {
			a[my_rank][0] = i;
			a[my_rank][1] = 0;
		}
		else
			a[my_rank][1]++;
	}
	printf("runtime:\n");
	output();

   	return 0; 
}

