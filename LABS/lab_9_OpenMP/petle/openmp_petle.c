#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
    double a[WYMIAR][WYMIAR];
#pragma omp paraller for schedule(none) dynamic(a)
    for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

    // sekwencyjnie
    double suma=0.0;
    for(int i=0;i<WYMIAR;i++) {
        for(int j=0;j<WYMIAR;j++) {
            suma += a[i][j];
        }
    }

    printf("Suma wyrazow tablicy: %lf\n", suma);

    omp_set_nested(1);
    // podwojna petla - docelowo ro�wnolegle
    double suma_parallel=0.0; int i, j;
    // wiersz
    //#pragma omp parallel for ordered reduction(+:suma_parallel) schedule(static, 2) private(j) default(none) shared(a)
#pragma omp parallel for ordered reduction(+:suma_parallel) schedule(static) private(j) default(none) shared(a)
    for(i=0;i<WYMIAR;i++) {
        // int id_w = omp_get_thread_num();
#pragma omp ordered
        // kolumnowa schedule(static, 2)
        //#pragma omp parallel for reduction(+:suma_parallel) schedule(dynamic) private(j) firstprivate(i) default(none) shared(a)
//#pragma omp parallel for ordered reduction(+:suma_parallel) schedule(dynamic) private(j) firstprivate(i) default(none) shared(a)
        for(j=0;j<WYMIAR;j++) {
            // #pragma omp critical(suma_parallel)
            suma_parallel += a[i][j];
//#pragma omp ordered
            // dla dekompozycji� 1D
            printf("(%1d,%1d)-W_%1d ",j,i,omp_get_thread_num());
            // dla dekompozycji 2D
            // printf("(%1d,%1d)-W_%1d,%1d ",j,i,id_w,omp_get_thread_num());
        }
        //#pragma omp ordered
        printf("\n");
    }
    printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
}
