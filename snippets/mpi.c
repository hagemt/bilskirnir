#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi/mpi.h>
#define MESSAGE "Greetings from process %d!"
#define MESSAGE_SIZE 100

int
main(int argc, char ** argv) {
  int r, p; /* Rank and process count */
  char msg[MESSAGE_SIZE];
  int src, dst = 0, tag = 50;
  size_t len;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &r);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  if (r != 0) {
    snprintf(msg, MESSAGE_SIZE, MESSAGE, r);
    len = strnlen(msg, MESSAGE_SIZE);
    MPI_Send(msg, len + 1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
  } else {
    for (src = 1; src < p; ++src) {
      MPI_Recv(msg, MESSAGE_SIZE, MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
      printf("%s\n", msg);
    }
  }
  MPI_Finalize();
  return (EXIT_SUCCESS);
}
