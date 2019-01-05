#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

int thread_count;
double total_int;
long long n = 1024;
int flag;

void* Thread_sum(void* rank);

double f (double x) {
  return x * x;
}

double Trap (
	     double left_endpt,
	     double right_endpt,
	     int trap_count,
	     double base_len) {
  double estimate, x;
  int i;

  estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
  for (i = 1; i <= trap_count - 1; i ++) {
    x = left_endpt + i * base_len;
    estimate += f(x);
  }
  estimate = estimate * base_len;
  return estimate;
}

int main(int argc, char* argv[]) {
	long thread;
	pthread_t* thread_handles;
	struct timeval start;
	struct timeval end;
	unsigned long diff;

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	gettimeofday(&start, NULL);
	for (thread = 0; thread < thread_count; thread ++)
		pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);

	for (thread = 0; thread < thread_count; thread ++)
		pthread_join(thread_handles[thread], NULL);
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

	printf("total_int = %lf, time = %ld\n", total_int, diff);
	free(thread_handles);
	return 0;
}

void* Thread_sum(void* rank) {
	long my_rank = (long) rank;
	long long local_n, local_n_rest;
	double a = 0.0, b = 3.0, h, local_a, local_b;
  	double local_int;

	h = (b - a) / n;
  	local_n = n / thread_count;
  	local_n_rest = n % thread_count;

 	local_a = a + my_rank * local_n * h;
 	local_b = local_a + local_n * h;
  	local_int = Trap(local_a, local_b, local_n, h);

	if (my_rank == thread_count - 1) {
    		local_int += Trap(local_b, b, local_n_rest, h);
  	}

	while (flag != my_rank);
	total_int += local_int;
	flag = (flag + 1) % thread_count;

	return NULL;
}


