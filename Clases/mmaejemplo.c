#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
  int pid;
  int *ptr;
  ptr = mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED,-1,0);
  pid = fork();
  
  //HIJO
  if (pid==0){
    *ptr=5;
    printf("soy el hijo ya escribi\n");
    sleep(2);
    printf("Leido por el hijo %d\n",*ptr );
    return 0;
  }

  //PADRE
  sleep(1);
  printf("Leido por el padre %d\n",*ptr);
  *ptr=(*ptr)*2;
  wait(NULL);
  return 0;
}