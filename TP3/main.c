#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <sys/mman.h>
//#include "mayus.h"
//#include "imprimir.h"
#include "tp3.h"
extern int letras[21];

void argumentos(int argc){
  if (argc==1) {
    printf("\nNo se ingresaron argumentos, se tomara stdin 0 como entrada\n\n ");
  }
}


void contador(){
  for(int i=0; i<21;i++){
    letras[i]=0;
  }
}

int main(int argc, char * const argv[]) {
		
	char delim[] = " ;:";
	char delim2[] = " ,;:.-_\n";
	char *input,* token2[2048],*token="",buffer2[100],buffer3[100];
	int len2,opt,flagf,j,pid1,pid2;
	char *ptr;
  int *x=0,*leido=0;
  
  sem_t *sem1, *sem2, *sem3, *sem4;
 
	ptr = mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED,-1,0);
	
  sem1=(sem_t *)ptr+ sizeof sem1;
  sem2=(sem_t *)ptr+ (sizeof sem1)*2;
  sem3=(sem_t *)ptr+ (sizeof sem1)*3;
  sem4=(sem_t *)ptr+ (sizeof sem1)*4;
  x=(int *)sem4+sizeof x;
  leido=(int *)x+sizeof leido;

  sem_init(sem1,1,0);
  sem_init(sem2,1,0);
  sem_init(sem3,1,0);
  sem_init(sem4,1,0);

	argumentos(argc);
	
	while ((opt=getopt(argc,argv,"f:")) != -1){
		switch (opt) {
			case 'f':
				input=optarg;
				flagf=1;
				break;
		}
	}

  //PRIMER HIJO
  pid1=fork();
  if(pid1 == 0){
    while (*x==0){   
      sem_wait(sem1);
      if (*leido>=1)
      {
      strncpy(buffer3,ptr,*leido);
      token=strtok(buffer3, delim);
      while (token != NULL){
        mayus(token);
        token = strtok(NULL, delim);
      }
    sem_post(sem3);
    }
      }
      
    return 0;
  }

  //SEGUNDO HIJO
  pid2=fork();
  if (pid2==0) {
  	contador();
    while (*x==0){
      sem_wait(sem2);
      strncpy(buffer2,ptr,*leido);
      j=0;
      token2[j]=strtok(ptr, delim2);
      while (token2[j] != NULL){
        len2=strlen(token2[j]);
        letras[len2-1]++;
        j++;
        token2[j] = strtok(NULL, delim2);
      }
    sem_post(sem4);     
    }
    imprimir();
    return 0;
  }

    //padre
  if(flagf==1){
    int archivo= open(input, O_RDWR , 0666);
    while((*leido=read(archivo,ptr,100))>0){
     	sem_post(sem1);
      sem_post(sem2);
      sem_wait(sem3);   
      sem_wait(sem4); 
      }
  }else{
    while ((*leido=read(0,ptr,100))>0){
      sem_post(sem1);
      sem_post(sem2);
      sem_wait(sem3);   
      sem_wait(sem4);     
    }
  }

  *x=1;

  //fin del programa
  sem_post(sem1);
  sem_post(sem2);
  wait(NULL);
  wait(NULL);
  printf("\n\n...TERMINADO...\n");
  munmap(ptr, 1024);
  return 0;
}
