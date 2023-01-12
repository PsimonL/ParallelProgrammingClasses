CCOMP = /usr/bin/mpicc
LOADER = /usr/bin/mpicc
MPI_run = /usr/bin/mpiexec -oversubscribe
OPT = -O2 -fopenmp
LIB =  -lm

all: mat_vec_row_MPI run

mat_vec_row_MPI: mat_vec_row_MPI.o
	$(LOADER) $(OPT) mat_vec_row_MPI.o -o mat_vec_row_MPI $(LIB)


mat_vec_row_MPI.o: mat_vec_row_MPI.c
	$(CCOMP) -c $(OPT) mat_vec_row_MPI.c $(INC)

run:
	$(MPI_run) -np 4 --oversubscribe  ./mat_vec_row_MPI

clean:
	rm -f *.o ./mat_vec_row_MPI