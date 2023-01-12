#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

typedef struct MyStruct
{
    int numInt;
    double numDouble;
    char fullName[20];
};

int main(int argc, char **argv)
{
    int rank, ranksent, packet_size, ssize, size, source, place, dest, tag, i;
    MPI_Status status;
    void *bufor;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > 1)
    {

        if (rank == 0)
        {
            dest = 1;
            tag = 0;
            packet_size = 0;
            ssize = 0;
            struct MyStruct obj = {111, 123.456, "SzymonRogowski"};
            MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &ssize);
            packet_size += ssize;
            MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &ssize);
            packet_size += ssize;
            MPI_Pack_size(20, MPI_CHAR, MPI_COMM_WORLD, &ssize);
            packet_size += ssize;

            bufor = (void *)malloc(packet_size);

            place = 0;

            MPI_Pack(&obj.numInt, 1, MPI_INT, bufor, packet_size, &place, MPI_COMM_WORLD);
            MPI_Pack(&obj.fullName, 20, MPI_CHAR, bufor, packet_size, &place, MPI_COMM_WORLD);
            MPI_Pack(&obj.numDouble, 1, MPI_DOUBLE, bufor, packet_size, &place, MPI_COMM_WORLD);

            MPI_Send(&packet_size, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);

            MPI_Send(bufor, place, MPI_PACKED, dest, 1, MPI_COMM_WORLD);

            printf("processID = %d \n", status.MPI_SOURCE);
            printf("numInt = %d, fullName = %s, numDouble = %f \n", obj.numInt, obj.fullName, obj.numDouble);
        }
        else
        {
            struct MyStruct obj2nd = {111, 123.456, "SzymonRogowski"};
            tag = 0;
            packet_size = 0;
            MPI_Recv(&packet_size, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
            bufor = (void *)malloc(packet_size);
            MPI_Recv(bufor, packet_size, MPI_PACKED, rank - 1, 1, MPI_COMM_WORLD, &status);

            MPI_Unpack(bufor, packet_size, &place, &obj2nd.numInt, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(bufor, packet_size, &place, &obj2nd.fullName, 20, MPI_CHAR, MPI_COMM_WORLD);
            MPI_Unpack(bufor, packet_size, &place, &obj2nd.numDouble, 1, MPI_DOUBLE, MPI_COMM_WORLD);

            printf("processID = %d \n", status.MPI_SOURCE);
            printf("numInt = %d, fullName = %s, numDouble = %f \n", obj2nd.numInt, obj2nd.fullName, obj2nd.numDouble);

            obj2nd.numInt += 10;

            if (rank < 5){
                bufor = 0;
                packet_size = 0;
                ssize = 0;
                MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &ssize);
                packet_size += ssize;
                MPI_Pack_size(20, MPI_CHAR, MPI_COMM_WORLD, &ssize);
                packet_size += ssize;
                MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &ssize);
                packet_size += ssize;

                bufor = (void *)malloc(packet_size);
                place = 0;

                MPI_Pack(&obj2nd.numInt, 1, MPI_INT, bufor, packet_size, &place, MPI_COMM_WORLD);
                MPI_Pack(&obj2nd.fullName, 20, MPI_CHAR, bufor, packet_size, &place, MPI_COMM_WORLD);
                MPI_Pack(&obj2nd.numDouble, 1, MPI_DOUBLE, bufor, packet_size, &place, MPI_COMM_WORLD);

                MPI_Send(&packet_size, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

                MPI_Send(bufor, place, MPI_PACKED, rank + 1, 1, MPI_COMM_WORLD);
            }
        }
    }
    else
        printf("Pojedynczy proces o randze: %d (brak komunikatA3w)\n", rank);

    MPI_Finalize();
    return (0);
}
