#include <stdio.h>
#include<pthread.h>


static int counter;
static int barier;
pthread_mutex_t muteks;
int LICZBA_W_MAX;
pthread_cond_t cond;

void bariera(int bariera){
   pthread_mutex_lock (&muteks);
   counter++;
   barier++;
   // printf("barier = %d\n", barier);
   // printf("counter = %d\n", counter);
   // pthread_cond_init(&cond, NULL); Doesnt work with uncommented, why?
      if (barier == LICZBA_W_MAX){
      // if (counter >= LICZBA_W_MAX * barier){
         barier = 0;
	 pthread_cond_broadcast(&cond);         
      } else {
         pthread_cond_wait(&cond, &muteks);
      }
   pthread_mutex_unlock( &muteks ); // NO pthread_mutex_signal( &muteks );
}

void bariera_init(int LICZBA_W){
   counter = 0;
   barier = 0;
   LICZBA_W_MAX = LICZBA_W;
   pthread_cond_init(&cond, NULL);
   pthread_mutex_init(&muteks, NULL);
}
