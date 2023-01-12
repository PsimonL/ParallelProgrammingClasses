#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

//double funkcja ( double x );		

double fun ( double x ){ return( sin(x) ); }

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=0;

static double calka_global=0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;
static double dx;
static double pp;

pthread_mutex_t muteks; 

void* calka_fragment_petli_w(void* arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w){

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;
  dx = dx_adjust;
  pp = (b-a)/l_w;
  
  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);

  
  // tworzenie struktur danych do obs³ugi wielow¹tkowoœci
  pthread_t *threads;
  int ids[l_w];

  // tworzenie w¹tków
  threads = (pthread_t *)malloc(l_w * sizeof(pthread_t));
  for(int i = 0; i < l_w; i++){
    ids[i] = i;
  }
    pthread_mutex_init( &muteks, NULL);
    for(int i = 0; i < l_w; i++){
      pthread_create(&threads[i], NULL, calka_fragment_petli_w, &ids[i]);
    }

     // oczekiwanie na zakoñczenie pracy w¹tków
    for(int i = 0; i < l_w; i++){
      pthread_join(threads[i],NULL);
    }

  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk){

  int my_id = *((int*)arg_wsk);

  double a, b, dx; // sk¹d pobraæ dane a, b, dx, N, l_w ? 
  int N, l_w;      // wariant 1 - globalne

  // a = a_global; // itd. itp. - wartoœci globalne nadaje calka_zrownoleglenie_petli

  // dekompozycja cykliczna
  double my_start = my_id*pp;
  double my_end = my_start + pp;
  double my_stride = dx;

  // dekompozycja blokowa
  //int my_start = 0;
  //int my_end = 0;
  //int my_stride = 0;

  // something else ? (dekompozycja blokowo-cykliczna)

  printf("\nW¹tek %d: my_start %lf, my_end %lf, my_stride %lf\n", 
	 my_id, my_start, my_end, my_stride);

  double calka = 0.0;
  for(double i=my_start; i<my_end-dx; i+=my_stride){

    //double x1 = a + i*dx;
    calka += 0.5*dx*(fun(i)+fun(i + dx));
       //printf("i %d, x1 %lf, funkcja(x1) %lf, ca³ka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka)

  }
  pthread_mutex_lock( &muteks );
  calka_global = calka_global + calka;
  pthread_mutex_unlock( &muteks );
  pthread_mutex_destroy(&muteks);
  pthread_exit( NULL );
}

