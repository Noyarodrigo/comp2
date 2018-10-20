#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int partes(int num,char * input);
int main(int argc, char * argv[]){
  int fdo,fdi,leido,x=1;
  int t,flags,flagn,flagh,flago=0,flagi,size,num;
  char opt,input[30],output[30],aux[30],n,s,h,o,i;

    if (argc==1) {
      printf("Este programa necesita argumentos, use la opcion -h para desplegar la ayuda\n");
    }
    while ((opt=getopt(argc,argv,"hn:s:o:i:")) != -1){
      switch (opt) {
        case 'h':
                  flagh=1;
                  break;
        case 'n':
                  flagn=1;
                  num=atoi(optarg);
                  break;
        case 's':
                  flags=1;
                  size=atoi(optarg);
                  break;;
        case 'o':
                  strcpy(output, optarg);
                  strcpy(aux, optarg);
                  flago=1;
                  break;
        case 'i':
                  fdi = open(optarg, O_RDONLY);
                  strcpy(input, optarg);
                  flagi=1;
                  break;
      }

      if (flagh==1) {
        printf("AYUDA\n Se debe respetar el formato ./dividir -s xx (o -n xx) -i [archivo_entrada] -o [archivo_salida] \n\t-n Cantidad de partes en que se quiere dividir. \n\t-s Tamanio, se crearan tantos archivos como sean necesarios max 2048. \n");
        return 0;
      }

      if (flago==1) {
        if (flags==1) {
          char buff[size];
          while((leido = read(fdi, buff, size)) > 0)
          {
              sprintf(output, "%s-%d", aux, x);
              fdo = open(output, O_CREAT|O_RDWR,0666);
              write(fdo,buff,leido);
              close(fdo);
              x++;
          }
          printf("\nSe han creado %d partes con un tamanio de %d\n",x-1,size );
          return 0;
        }
        if (flagn==1) {
          int u = partes(num,input);
          printf("Tamanio de las partes redondeadas hacia arriba: %d\n",u );
          char buff[u];
          for (int w = 0; w < num; w++) {
            leido = read(fdi, buff, u);
            sprintf(output, "%s-%d", aux, w+1);
            fdo=open(output, O_CREAT|O_RDWR, 0666);
            write(fdo,buff,leido);
            close(fdo);
          }
        }
      }
    }
    if (flago==0){
      if (flagn==1) {
        printf("------------------------------\n");
        printf("NO SE ESPECIFICO NINGUNA SALIDA\n");
        printf("      SALIDA POR STDOUT\n");
        int u = partes(num,input);
        printf("Tamanio de las partes redondeadas hacia arriba: %d\n",u );
        printf("------------------------------\n");

        char buff[u];
        for (int w = 0; w < num; w++) {
          leido = read(fdi, buff, u);
          printf("Parte numero: %d\n",w+1 );
          printf("------------------------------\n\n\n");
          sprintf(output, "%s-%d", aux, w+1);
          write(1,buff,leido);
          printf("------------------------------\n\n\n");
          }
        close(fdi);
        }
      if (flags==1) {
        int w=0;
        char buff[size];
        printf("------------------------------\n");
        printf("NO SE ESPECIFICO NINGUNA SALIDA\n");
        printf("      SALIDA POR STDOUT\n\n");
        printf("Tamanio ingresado: %d\n",size);
        while((leido = read(fdi, buff, size)) > 0){
          printf("\n------------------------------\n\n");
          printf("Parte numero: %d\n",w+1 );
          printf("------------------------------\n\n");
          write(1,buff,leido);

          w++;
        }
        close(fdi);
      }
    }

  return 0;
}

int partes(int num,char * input){
  FILE *fd;
  fd=fopen(input,"r");
  fseek(fd,0l, SEEK_END);
  int k=ftell(fd);
  float y= (float)k/num;
  int u=ceil(y);
  printf("Tamanio del archivo: %d\n",k );
  printf("Partes ingresadas: %d\n",num );
  printf("Nombre del archivo: %s\n",input );
return u;
}
