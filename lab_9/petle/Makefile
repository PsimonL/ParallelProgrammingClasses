CCOMP = gcc
LOADER = gcc


#OPT = -O3

start: clean openmp_petle_simple

openmp_petle_simple: 
    gcc -fopenmp openmp_petle_simple.c -o openmp_petle_simple

clean:
    rm -f *.o openmp_petle_simple

