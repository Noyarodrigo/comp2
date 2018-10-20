
#include <stdio.h>
int main(int argc, char * argv[]){

  printf ("Cantidad de parametros  %d \n",argc);
  for (int i = 0; i < argc; i++) {
      printf("Elemento %d: %s \n",i,*argv);
      argv++;
    //printf("Elemento %d: %s \n",i,*argv++); es lo mismo, el ++ se hace al final

  }
  return 0;
}
