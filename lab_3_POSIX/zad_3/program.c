#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define LICZBA_W_MAX 20

typedef struct
{
    int first, second, third;
} ExampleStructure;


void *zadanie_watku(void *arg_wsk)
{
    printf("Dzialam: function\n");
    ExampleStructure *pointer = (ExampleStructure*)arg_wsk; // jawne rzutowanie wskaŸnika na typ ExampleStructure 
    pointer->first += 13;
    pointer->second += 151;
    pointer->third  += 1243;

    ExampleStructure objFunc;
    objFunc.first = 100;
    objFunc.second = 100;
    objFunc.third  = 100;
    printf("lokalne:\n");  
    printf("objFunc.first = %d, objFunc.second = %d, objFunc.third  = %d\n", objFunc.first, objFunc.second, objFunc.third );
    printf("globalna - zadanie_watku:\n"); 
    printf("pointer->first = %d, pointer->first = %d, pointer->first = %d\n", pointer->first, pointer->second, pointer->third );
    return (NULL);
}

int main()
{
    printf("Dzialam: start\n");
    pthread_t tid;

    ExampleStructure objStruct;
    objStruct.first = objStruct.second = objStruct.third = 10;
    pthread_create(&tid, NULL, zadanie_watku, (void*)&objStruct);
    pthread_create(&tid, NULL, zadanie_watku, (void*)&objStruct);

    pthread_join(tid, NULL);

    printf("globalne - main:\n");
    printf("objStruct.first = %d, objStruct.second = %d, objStruct.third  = %d\n", objStruct.first, objStruct.second, objStruct.third );
    
    printf("Dzialam: end\n");

    pthread_exit(NULL);
}

