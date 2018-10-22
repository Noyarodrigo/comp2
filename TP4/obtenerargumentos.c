#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct argumentos {
    char direccion[40];
    char barra[40];
    char palabra[40];
};

struct argumentos obtenerargumentos(char * buff){
	char *token="", delim[]=" ",aux[1024];
  struct argumentos arg;
	strcpy(aux,buff);
	token=strtok(aux, delim);
  strcpy(arg.direccion,token);
  printf("Direccion: %s\n", arg.direccion);
	token = strtok(NULL, delim);
  strcpy(arg.palabra,token);
  printf("Palabra: %s\n",arg.palabra );
  token=strtok(arg.direccion,"/");
  token=strtok(NULL,"/");
  while( token != NULL ) {
    strcat(arg.barra,"/");
    strcat(arg.barra,token);
    token = strtok(NULL, "/");
   }

  printf("BARRA: %s\n",arg.barra );
  return arg;
};
