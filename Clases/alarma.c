//esto es para el programa signal.c
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <assert.h>
int main(int argc, char * argv[]) {
  //para asegurarme de que ponga argumentos
  assert(argc=2);
  while (1) {
    kill(atoi(argv[1]),14);
    sleep(5);
  }
  return 0;
}
