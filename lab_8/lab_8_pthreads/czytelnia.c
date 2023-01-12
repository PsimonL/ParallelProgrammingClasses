#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/
pthread_mutex_t wMutex;
pthread_mutex_t rMutex;
pthread_cond_t wCond;
pthread_cond_t rCond;

int readAwaits = 0;
int writeAwaits = 0;


int my_read_lock_lock(czytelnia_t *czytelnia_p){
    if (czytelnia_p->writters > 0){
        pthread_mutex_lock(&rMutex);
        readAwaits ++;
        readAwaits --;
        pthread_cond_wait(&rCond, &rMutex);
        pthread_mutex_unlock(&rMutex);
    }
    czytelnia_p->readers;
    pthread_cond_broadcast(&rCond);
}

int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    czytelnia_p->readers --;
    if (czytelnia_p->readers == 0) {
        pthread_cond_broadcast(&wCond);
    }
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
    czytelnia_p->writters --;
    if (readAwaits != 0)pthread_cond_signal(&rCond);
    else pthread_cond_signal(&wCond);
}


void inicjuj(czytelnia_t* czytelnia_p){
    pthread_mutex_init(&wMutex, NULL);
    pthread_mutex_init(&rMutex, NULL);
}

void czytam(czytelnia_t* czytelnia_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy

// sprawdzenie warunku poprawności i ewentualny exit
// warunek: if( l_p>1 || (l_p==1 && l_c>0) || l_p<0 || l_c<0 ) { printf(...); exit(0); }

    printf("\nReading\n");
    printf("NOreaders: %d === NOwriters: %d \n", czytelnia_p->readers, czytelnia_p->writters);
    printf("NOrWait: %d === NOwWait: %d \n", readAwaits, writeAwaits);
    usleep(rand() % 300000);
    pthread_mutex_lock(&wMutex);
    pthread_mutex_lock(&rMutex);

    if (czytelnia_p->writters > 1 || (czytelnia_p->writters == 1 && czytelnia_p->readers > 0)
    || czytelnia_p->writters < 0 || czytelnia_p->readers < 0){
        printf("error occured\n");
        exit(0);
    }

    pthread_mutex_unlock(&wMutex);
    pthread_mutex_unlock(&rMutex);
}

void pisze(czytelnia_t* czytelnia_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy

// sprawdzenie warunku poprawności i ewentualny exit
// warunek: if( l_p>1 || (l_p==1 && l_c>0) || l_p<0 || l_c<0 ) { printf(...); exit(0); }

    printf("\nWritting\n");
    printf("NOreaders: %d === NOwriters: %d \n", czytelnia_p->readers, czytelnia_p->writters);
    printf("NOrWait: %d === NOwWait: %d \n", readAwaits, writeAwaits);

    usleep(rand() % 300000);
    pthread_mutex_lock(&wMutex);
    pthread_mutex_lock(&rMutex);

    if (czytelnia_p->writters > 1 || (czytelnia_p->writters == 1 && czytelnia_p->readers > 0)
        || czytelnia_p->writters < 0 || czytelnia_p->readers < 0){
        printf("error occured\n");
        exit(0);
    }
    pthread_mutex_unlock(&wMutex);
    pthread_mutex_unlock(&rMutex);
}


