#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct argumentos {
    char direccion[40];
    char extension[40];
};

struct argumentos obtenerargumentos(char * buff){
	char *token="",aux[1024];
  struct argumentos arg;
	strcpy(aux,buff);
  strcpy(arg.direccion,aux);
  printf("Archivo: %s\n", arg.direccion);
	token=strtok(aux, ".");
	token = strtok(NULL, ".");
  strcpy(arg.extension,token);
  printf("Extension: %s\n",arg.extension );
  return arg;
};
