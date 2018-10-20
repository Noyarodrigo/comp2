#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
    int pid,pph[2],php[2],leido,i,leer;
    int buffer[100];
    pipe(pph);
    pipe(php);
    pid=fork();
    if(pid == 0){ //si es cero es que se ejecuta el hijo y este codigo es para que haga algo distinto al padre
      close(php[0]);
      close(pph[1]);
      while ((leido=read(pph[0],buffer,sizeof buffer))>0){
        for (i=0; i<leido; i++) {
          buffer[i]=toupper(buffer[i]);
	        printf("%c\n",buffer[i]);
          }
        write(php[1],buffer,leido);
    	 }
      return 0;
      }
  //PADRE
  close(pph[0]);
  close(php[1]);
  while ((leer=read(0,buffer,sizeof buffer))>0){
    write(pph[1],buffer,leer);
  }
  close(pph[1]);
  while ((leer=read(php[0],buffer,sizeof buffer))>0){
    write(1,buffer,leer);
  }
return 0;
}
