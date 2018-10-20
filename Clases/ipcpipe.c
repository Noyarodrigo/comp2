#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int x=2;

int main(int argc, char * argv[]){
    int pid,pd[2],buffer[12],leido;
    pipe(pd);
    pid=fork();
    if(pid == 0){ //si es cero es que se ejecuta el hijo y este codigo es para que haga algo distinto al padre
      x=10;
      close(pd[1]);
      while ((leido=read(pd[0],buffer,sizeof buffer))>0){
        write(1,buffer,leido);
      }
      printf("X hijo: %p\n",&x);
      return 0;
    }
    close(pd[0]);
    write(pd[1],"hola hijo\n",10);
    write(pd[1],"chau hijo\n",10);
    close(pd[1]);
    wait(NULL);
    printf("X padre: %p\n",&x);
    return 0;
}
