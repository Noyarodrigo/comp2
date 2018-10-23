#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


char * parse(char * buff2, char * palabra){
  char pila[1024], buscar[50];
  char * buff1 = malloc(sizeof(char)*1024);


  strncpy(pila,buff2, strlen(buff2));
  strncpy(buscar, palabra, strlen (palabra));

  char * puntero=strstr(pila,buscar);
  if(puntero!=NULL){
      char* puntero_aux=puntero;
      while(*puntero!='>'){puntero--; }
      puntero++;
      while(*puntero_aux!='<'){puntero_aux++;}
      strncat(buff1,puntero,(puntero_aux-puntero));
      //printf("%s\n",buff1 );
      return buff1;
    }
return "";
}
