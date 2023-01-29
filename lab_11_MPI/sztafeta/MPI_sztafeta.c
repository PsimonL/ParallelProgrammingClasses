#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, ranksent, size, source, process_id, tag, i;
    MPI_Status status;
    int data = 0, numberOfRepeats = 2;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int loop_break = 1;
    if (size > 1)
    {
        if (rank == 0)
        {
            for (int i = 0; i < numberOfRepeats; i++)
            {
                process_id = 1;
                tag = 0;
                MPI_Send(&data, 1, MPI_INT, process_id, tag, MPI_COMM_WORLD);
                printf("data = [%d] FROM process: (%d)\n", data, process_id);
                if (!loop_break) break;
                MPI_Recv(&data, 1, MPI_INT, process_id + 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("data = [%d] TO process (%d)\n", data, status.MPI_SOURCE);
            }
        }
        else
        {
            for (int i = 0; i < numberOfRepeats; i++)
            {
                tag = 0;
                MPI_Recv(&data, 1, MPI_INT, rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("data = [%d] FROM process: (%d)\n", data, status.MPI_SOURCE);
                data++;
                if (rank < 2){
                    MPI_Send(&data, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);
                    printf("data = [%d] TO process: (%d)\n", data, rank + 1);
                }else{
                    if (!loop_break) break;
                    MPI_Send(&data, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                    printf("data = [%d] TO process: (%d)\n", data, 0);
                }
            }
        }
    }
    else
        printf("Single processs with rank: %d (no sense) \n", rank);

    MPI_Finalize();
    return (0);
}

