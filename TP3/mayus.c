#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void mayus(char *token){
  int i;
  char *palabras[]={"He","She","It","south","then","state"};
  char *palabras2[]={"HE","SHE","IT","SOUTH","THEN","STATE"};
  char *bla;
   for (i = 0; i < 6; i++) {
            bla=palabras[i];
            int x=strcmp(token,bla);
            if (x==0){
              printf(" %s",palabras2[i] );
              break;
            }
          }
          if (i==6) {
            printf(" %s", token );
          }
}