#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

//int comm_number, loop_time = 0;
//double local_start, local_finish, local_elapsed, elapsed;
//int i, rank_mark, distance;
int my_rank;
//int local_int_recv;
//int comm_sz, local_int;

int main(void) {
	int comm_sz, local_int, comm_number, loop_time = 0;
	double local_start, local_finish, local_elapsed, elapsed;
	int i, rank_mark, distance;
	//int my_rank;
	int local_int_recv;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	local_int = my_rank + 1;
	//printf("my_rank = %d, local_int = %d\n", my_rank, local_int);
	rank_mark = my_rank;
	distance = 1;
	comm_number = comm_sz;
	while (comm_number != 1) {
		loop_time += 1;
		comm_number /= 2;
	}

	//MPI_Barrier(MPI_COMM_WORLD);
	local_start = MPI_Wtime();

	//code to be timed start
	for (i = 0; i < loop_time; i++) {
		if (rank_mark % 2 == 0) {
			MPI_Send(&local_int, sizeof(local_int), MPI_INT, my_rank + distance, 0, MPI_COMM_WORLD);
			MPI_Recv(&local_int_recv, sizeof(local_int_recv), MPI_INT, my_rank + distance, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			//printf("my_rank = %d, from %d receive = %d\n", my_rank, my_rank + distance, local_int_recv);
		}
		else {
			MPI_Send(&local_int, sizeof(local_int), MPI_INT, my_rank - distance, 0, MPI_COMM_WORLD);
			MPI_Recv(&local_int_recv, sizeof(local_int_recv), MPI_INT, my_rank - distance, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
			//printf("my_rank = %d, from %d receive = %d\n", my_rank, my_rank - distance, local_int_recv);
		}
		local_int += local_int_recv;
		//printf("my_rank = %d, local_int = %d\n", my_rank, local_int);
		rank_mark /= 2;
		distance *= 2;
		
	}
	//code to be timed end

	local_finish = MPI_Wtime();
	local_elapsed = local_finish - local_start;
	MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

		if (my_rank == 0) {
			printf("Elapsed time = %e seconds\n", elapsed);
		}
	printf("my_rank = %d, my number = %d\n", my_rank, local_int);

	MPI_Finalize();
	return 0;
}
