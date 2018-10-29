#include <stdio.h>
#include <unistd.h>
#include <string.h>

char * parse(char * buff2, char * palabra){
  char *token="";
  char delim[] = "\n";
  char pila[8192], buscar[50];
  char *ret;
  strcpy(pila,buff2);
  strcpy(buscar, palabra);
  token=strtok(buff2, delim);
  while (token != NULL){
    ret=strstr(token,buscar);
      if (ret!=NULL){
        return token;
      }
    token = strtok(NULL, delim);
  }
  return "Palabra no encontrada";
}
