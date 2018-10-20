#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int letras[21];
void imprimir(){
  printf("\n\n +++++++++++++++++++++++++++++++++++++++");
    for (int i = 0; i < 21; i++) {
      if (letras[i]!=0){
        printf("\n\t+Hay %d palabras de %d letras +",letras[i],i+1 );
      }
    }
    printf("\n\n +++++++++++++++++++++++++++++++++++++++");  
}