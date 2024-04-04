#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get number of processes and check that 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //printf("Size = %d", size);
    //if(size != 4)
    //{
    //    printf("This application is meant to be run with 3 MPI processes.\n");
    //    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    //}

    // Get my rank
    int my_rank;
    my_rank=0;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Define my value
    int my_values[5];
    for(int i = 0; i < 5; i++)
    {
        // my_values[i] = my_rank * 100 + i;
        my_values[i] =100*my_rank + i;
    }
    printf("Process %d, my values = %d, %d, %d, %d, %d.\n", my_rank, my_values[0], my_values[1], my_values[2], my_values[3], my_values[4]);

    int b[5];
    for(int i = 0; i < 5; i++){
        b[i] = my_rank;
    }

//MPI_Alltoall(&my_values[2], 2, MPI_INT, &b[0], 2, MPI_INT, MPI_COMM_WORLD);
//MPI_Scatter(&my_values[2], 2, MPI_INT, &b[1], 2, MPI_INT, 3, MPI_COMM_WORLD);
    MPI_Bcast(&my_values[2], 2, MPI_INT, 2, MPI_COMM_WORLD);
//MPI_Allreduce(&my_values[2], &b[1], 5, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
//MPI_Reduce(&my_values[2], &b[1], 5, MPI_INT, MPI_SUM, 2, MPI_COMM_WORLD);
//MPI_Allgather(&my_values[2], 2, MPI_INT, &b[1], 2, MPI_INT, MPI_COMM_WORLD);

    printf("Values collected on process %d: %d, %d, %d, %d, %d.\n", my_rank, b[0],b[1], b[2], b[3], b[4]);
    printf("\n");
    MPI_Finalize();

    return EXIT_SUCCESS;
}
