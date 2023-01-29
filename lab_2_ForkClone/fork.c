#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pomiar_czasu.h>

int zmienna_globalna=0;

main(){
  
  int pid, wynik, i;
//  inicjuj_czas();
  
//  for(i=0;i<10000;i++){
    
    pid = fork(); 			
    
    if(pid==0){ 			
      
      zmienna_globalna++;
	
      
      char *argv[] = {"Szymon Rogowski", NULL};
      wynik=execv("./program", argv); 
        if(wynik==-1) 
           printf("Proces potomny nie wykonal programu\n");

      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
//  }
//  drukuj_czas();
  
}

  
