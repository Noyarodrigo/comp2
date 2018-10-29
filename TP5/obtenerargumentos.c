#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct argumentos {
    char direccion[40];
    char extension[40];
    char protocolo[40];
    char version[40];

};

struct argumentos obtenerargumentos(char * buff){
	char *token="",aux[1024];
  struct argumentos arg;
	strcpy(aux,buff);
  token=strtok(aux, "\n");
  strcpy(arg.direccion,token);
  token = strtok(arg.direccion, " ");
  strcpy(arg.protocolo,token);
  token = strtok(NULL, " ");
  strcpy(arg.direccion,token);
  token = strtok(NULL, " ");
  strcpy(arg.version,token);
  strcpy(aux,arg.direccion);
  token = strtok(aux,".");
  token = strtok(NULL,".");
  strcpy(arg.extension,token);

  return arg;
};
