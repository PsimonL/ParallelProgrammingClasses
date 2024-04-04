#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"pomiar_czasu.h"

#define mod
 
const int liczba = 5000000;

int main(){

  double a, b, c;
  int i,j,k,l;

#ifdef mod 
  double t1, t2;
#endif

  inicjuj_czas();
  k = -50000;
  for(i=0;i<liczba;i++){

    printf("%d ",k+i);

  }
  printf("\n");
  printf("Czas wykonania %d operacji wejscia/wyjscia: \n",liczba);
  drukuj_czas();

#ifdef mod
  t1 = czas_zegara(); t2 = czas_CPU(); 
#endif

  a = 1.000001;
  for(i=0;i<liczba;i++){

    a = 1.000001*a+0.000001; 

  }

#ifdef mod
  t1 = czas_zegara() - t1; t2 = czas_CPU() - t2;
#endif

  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("Czas wykonania %d operacji arytmetycznych: \n",liczba);

#ifdef mod
  printf("Czas zegarowy: t1 = %f \n", t1);
  printf("Czas CPU: t2 = %f \n", t2);
#endif

}
