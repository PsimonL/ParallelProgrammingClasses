#include <stdio.h>
#include <mpi.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    int max_liczba_wyrazow=0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Read the maximum number of terms from the command line
    if (rank == 0) {
        printf("Enter the maximum number of terms to use in the Leibniz series approximation of PI: ");
        scanf("%d", &max_liczba_wyrazow);
    }

    // Broadcast the maximum number of terms to all processes
    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the local sum for each process
    double local_sum = 0.0;
    for (int i = rank; i < max_liczba_wyrazow; i += size) {
        double term = 1.0 / (2 * i + 1);
        if (i % 2 == 0) {
            local_sum += term;
        } else {
            local_sum -= term;
        }
    }

    // Combine the local sums using MPI_Reduce
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    global_sum *= 4;
    
    // Print the result
    if (rank == 0) {
        printf("Approximation of PI using %d terms = \t%.10f\n", max_liczba_wyrazow, global_sum);
        printf("Approximation of PI from cmath \t%20.15lf\n", M_PI);
    }

    MPI_Finalize();
    return 0;
}