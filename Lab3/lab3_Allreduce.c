#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(void) {
  int my_rank, comm_sz, local_int, total_int;
  double local_start, local_finish, local_elapsed, elapsed;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  local_int = my_rank + 1;

  MPI_Barrier(MPI_COMM_WORLD);
  local_start = MPI_Wtime();
  MPI_Allreduce(&local_int, &total_int, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  local_finish = MPI_Wtime();
  local_elapsed = local_finish - local_start;
  MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  if (my_rank == 0) {
    printf("Elapsed time = %e seconds\n", elapsed);
  }
  printf("my_rank = %d, my number = %d\n", my_rank, total_int);
  
  MPI_Finalize();
  return 0;
}
