#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char * argv[]){
  int i,t,flaga,flagb,flagh;
  char opt,h,b,a;
    if (argc==1) {
      printf("Este programa necesita argumentos\n");
    }
    while ((opt=getopt(argc,argv,"ab:h")) != -1){
      switch (opt) {
        case 'h':
                  flagh=1;
                  break;
        case 'b':
                  flagb=1;
                  t=atoi(optarg);
                  break;
        case 'a':
                 flaga=1;
                 break;
      }

      if (flagh==1) {
        printf("AYUDA\n");
      }
      if (flagb==1) {
        printf("4 veces el valor: %d\n",t*4);
      }

      if (flaga==1) {
        printf("Auxiliar\n");
      }

    }
return 0;
}
