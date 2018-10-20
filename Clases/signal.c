#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int num){
    printf("\nLa señal que me llego es la: %d\n", num);
}

int main() {
  signal(2,handler);
  signal(3,handler);
  char buffer[100];
  printf("Mi proceso es el %d\n",getpid());
  read(0,buffer,sizeof buffer);
  return 0;
}
