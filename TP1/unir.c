#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void consola(char * input, char * aux);
void sto();
void sto2(char * output);
int main(int argc, char * argv[]){

int flagh,flagi,flago=0;//flags
int leido,x=1,fdi,fdo,fd;
char opt,h,o,i;//opciones switch
char buff[2048],input[30],output[30],aux[30];
if (argc==1) {
  printf("\nSe recomienda usar argumentos, ingrese la opcion -h para desplegar la ayuda\n\n ");

}

while ((opt=getopt(argc,argv,"o:i:h")) != -1){
  switch (opt) {

    case 'h':
          flagh=1;
          break;
    case 'o':
          flago=1;
          strcpy(output, optarg);
          break;
    case 'i':
          flagi=1;
          strcpy(input, optarg);
          strcpy(aux, optarg);
          break;
  }
}
  if (flagh==1) {
    printf("\nAYUDA\n Se debe respetar el formato ./unir -i [archivo_Entrada(solo el nombre sin -*)] -o [archivo_salida(se puede omitir)] \n EJ) ./unir -i cortado -o unido\n\n\nSe puede ingresar un ls [nombre-*] | ./unir (-o opcional)\n");
    return 0;
  }
  if (flagi==1) {
    if (flago==1) {
      FILE *fd;
      while(1){
        sprintf(input, "%s-%d", aux, x);
        fd=fopen(input,"r");
        if (fd==NULL) {
          printf("\n...Terminado...\n");
          exit(1);
        }else{
          printf("Uniendo: %s\n",input );
          fdi = open(input, O_RDONLY);
          leido = read(fdi, buff, 2048);
          fdo = open(output, O_CREAT|O_WRONLY|O_APPEND, 0660);
          write(fdo,buff,leido);
          close(fdo);
          x++;
          }
        }
      }
      if (flago==0) {
        consola(input, aux);
        }
    }else{
      if (flago==0) {
        sto();
      }else{
        sto2(output);
      }
    }

return 0;
}

void consola(char * input, char * aux){
  int x=1, leido,fdi;
  char buff[2048];
  printf("------------------------------\n");
  printf("NO SE ESPECIFICO NINGUNA SALIDA\n");
  printf("      SALIDA POR STDOUT\n");
  printf("------------------------------\n");
  FILE *fd;
  while(1){
    sprintf(input, "%s-%d", aux, x);
    fd=fopen(input,"r");
    if (fd==NULL) {
      printf("\n...Terminado...\n");
      exit(1);
    }else{
      fdi = open(input, O_RDONLY);
      leido = read(fdi, buff, 2048);
      write(1,buff,leido);
      x++;
      }
    }
}

void sto(){
  int fdi,leido;
  char buff[2048],buffer[300];
  printf("\n------------------------------\n");
  printf("NO SE ESPECIFICO NINGUNA SALIDA\n");
  printf("      SALIDA POR STDOUT\n");
  printf("------------------------------\n");
  read(0, buffer, 300);
  char *primeraPalabra = strtok(buffer, "\n");
  char *token = primeraPalabra;
  fdi = open(token, O_RDONLY);
  leido = read(fdi, buff, 2048);
  write(1,buff,leido);
  close(fdi);
  while (token != NULL)
  {
  token = strtok (NULL, "\n");
  fdi = open(token, O_RDONLY);
  leido = read(fdi, buff, 2048);
  write(1,buff,leido);
  close(fdi);
  }
}

void sto2(char * output) {
  int fdi,fdo,leido;
  char buff[2048],buffer[300];
  read(0, buffer, 300);
  printf("\nUniendo...\n\n" );
  char *primeraPalabra = strtok(buffer, "\n");
  char *token = primeraPalabra;
  fdi = open(token, O_RDONLY);
  leido = read(fdi, buff, 2048);
  fdo = open(output, O_CREAT|O_WRONLY|O_APPEND, 0660);
  write(fdo,buff,leido);
  close(fdi);
  while (token != NULL)
  {
  token = strtok (NULL, "\n");
  fdi = open(token, O_RDONLY);
  leido = read(fdi, buff, 2048);
  write(fdo,buff,leido);
  close(fdi);
  }
  close(fdo);
  printf("\nTerminado...\n\n" );
}
