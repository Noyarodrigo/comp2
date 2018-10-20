#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int letras[21];
void contador(){
  for(int i=0; i<21;i++){
    letras[i]=0;
  }
}

void argumentos(int argc){
  if (argc==1) {
    printf("\nNo se ingresaron argumentos, se tomara stdin 0 como entrada\n\n ");
  }
}

int main(int argc, char * const argv[]) {

  int pid1,pid2,pph1[2],pph2[2],leido,i,j,leer,len,len2,opt,flagf;
  char buffer[1024];
  char aux[1024],aux2[1024];
  char * token2[2048];
  char *token="", *bla, *input;
  char *palabras[]={"bandera","provincias","las","los","Plata","Estado"};
  char *palabras2[]={"BANDERA","PROVINCIAS","LAS","LOS","PLATA","ESTADO"};
  char delim[] = " ,;:.";
  char delim2[] = " ,;:.-_\n";

  pipe(pph1);
  pipe(pph2);
  
  argumentos(argc);

  while ((opt=getopt(argc,argv,"f:")) != -1){
    switch (opt) {
      case 'f':
          input=optarg;
          flagf=1;
          break;
    }
  }
  
  //PRIMER HIJO
  pid1=fork();
  if(pid1 == 0){
    close(pph1[1]);
    close(pph2[0]);
    close(pph2[1]);
    while ((leido=read(pph1[0],aux,sizeof (aux)))>0){
      token=strtok(aux, delim);
      while (token != NULL){
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
          token = strtok(NULL, delim);
      }
    }
    return 0;
  }

  //SEGUNDO HIJO
  pid2=fork();
  if (pid2==0) {
    close(pph2[1]);
    close(pph1[0]);
    close(pph1[1]);
    sleep(2);
    contador();
    while ((leer=read(pph2[0],aux2,sizeof (aux2)))>0){
      j=0;
      token2[j]=strtok(aux2, delim2);
      while (token2[j] != NULL){
        len2=strlen(token2[j]);
        letras[len2-1]++;
        j++;
        token2[j] = strtok(NULL, delim2);
      }
    }
    printf("\n\n +++++++++++++++++++++++++++++++++++++++");
    for (i = 0; i < 21; i++) {
      if (letras[i]!=0){
        printf("\n\t+Hay %d palabras de %d letras +",letras[i],i+1 );
      }
    }
    printf("\n\n +++++++++++++++++++++++++++++++++++++++");
    close(pph2[0]);
    return 0;
  }

  //PADRE
  //Cerrar pipes que no uso
  close(pph1[0]);
  close(pph2[0]);
  
  //ESCRIBIR A LOS HIJOS
  if(flagf==1){
    int archivo= open(input, O_RDWR , 0666);
    while((leer=read(archivo,&buffer,sizeof buffer))>0){
      write(pph1[1],buffer,leer);
      write(pph2[1],buffer,leer);
      }
  }else{
    while ((leer=read(0,buffer,sizeof buffer))>0){
      write(pph1[1],buffer,leer);
      write(pph2[1],buffer,leer);
    }
  }
  //cerrar los pipes que ya no uso
  close(pph1[1]);
  close(pph2[1]);
  wait(NULL);
  wait(NULL);
  //fin del programa
  printf("\n\nTERMINADO\n");

  return 0;
}
