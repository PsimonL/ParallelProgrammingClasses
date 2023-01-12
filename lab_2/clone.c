#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include <pomiar_czasu.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  for(int i = 0; i < 100000; i++){
    *(argument)++;
    zmienna_globalna++;
  }

  /* int wynik; */
  /* wynik=execv("./program",NULL); */
  /* if(wynik==-1) */
  /*   printf("Proces potomny nie wykonal programu\n"); */

  return 0;
}

int main()
{

  void *stos;
  pid_t pid;
  int i; 
  // inicjuj_czas();
  stos = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

  /*for(i=0;i<1000;i++){

    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

    waitpid(pid, NULL, __WCLONE);}*/

  int zmienna_lokalna = 0;
  pid = clone(&funkcja_watku, (void*) stos+ROZMIAR_STOSU, CLONE_FS| 
  CLONE_FILES | CLONE_SIGHAND | CLONE_VM, zmienna_lokalna);

  // drukuj_czas();
  waitpid(pid, NULL, __WCLONE);
  free( stos );
  printf("Zmienna lokalna = %d\n", zmienna_lokalna);
  printf("Zmienna globalna = %d\n", zmienna_globalna);
}
