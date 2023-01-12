# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/bin/mpiexec -oversubscribe

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG  -fopenmp
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

all: MPI_test run 

run: MPI_test
	$(MPI_run) -np 3 MPI_test

# zaleznosci i komendy
MPI_test: MPI_test.o 
	$(LOADER) $(OPT) MPI_test.o -o MPI_test $(LIB)

# jak uzyskac plik MPI_test.o ?
MPI_test.o: MPI_test.c
	$(CCOMP) -c $(OPT) MPI_test.c $(INC) 

clean:
	rm -f *.o MPI_test
