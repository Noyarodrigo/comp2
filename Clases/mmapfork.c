#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/wait.h>

int * dir;
int pid,i;

void handler(){
  //*dir lee el contenido del puntero dir
    printf("El padre lee %d\n",*dir );
    kill(pid,SIGUSR2);
}

void handler2(){
    (*dir)++;
    kill(getppid(),SIGUSR1);
}

int main(int argc, char const *argv[]) {
  //argumentos
  //1- donde lo voy a poner al mapeo,2- cantidad a compartir 3-protecciones, 4- si voy a necesitar un archivo, 5- descriptor de arcivo
  //NULL es cuando no sabemos donde va a ir

  //la var dir guard un puntero a la primer pos de memoria del map
  dir=mmap(NULL,1,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
  pid=fork();
  if (pid==0) { //hijo
    signal(SIGUSR2,handler2);
    (*dir)++;
    kill(getppid(),SIGUSR1);
    while (*dir<10) {
      usleep(100);

    }
    return 0;
  }
  //padre
  signal(SIGUSR1,handler);
  //wait espera a que termina el hijo
  wait(NULL);
  return 0;
}
