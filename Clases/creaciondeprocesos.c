#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[]){
    int pid;
    printf("Hola\n");
    pid=fork();
    if(pid == 0){ //si es cero es que se ejecuta el hijo y este codigo es para que haga algo distinto al padre
      printf("soy el hijo mi pid es %d y mi padre %d\n",getpid(),getppid());
      return 0;
    }
    printf("soy el padre mi pid es %d y mi padre %d y mi hijo es %d\n",getpid(),getppid(),pid);
    return 0;
    
}

