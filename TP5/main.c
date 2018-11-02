#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/sendfile.h>
#include "tp5.h"

void argumentosvacios(int argc){
  if (argc==1) {
    printf("\n...Se tomara el archivo de confirguracion por defecto...\n\n ");
  }
}

struct argumentos {
    char direccion[40];
    char extension[40];
    char protocolo[40];
    char version[40];

};

struct configuracion {
    char puerto[10];
    char droot[50];
};

struct parametros{
  char lectura[1024];
  char ruta[100];
  int sockete;
};

void *hilo(void * paramain ){

  pthread_detach(pthread_self());

  char buff2[1000000], input[1024];
  int leido, fd;
  char ruta[150];

  struct argumentos arg1;
  struct stat st;
  struct parametros *paramhilo= (struct parametros *) paramain;
  int sd=paramhilo->sockete;

  strcpy(buff2,(*paramhilo).lectura);
  arg1=obtenerargumentos(buff2);
  snprintf(ruta,(strlen(paramhilo->ruta)+strlen(arg1.direccion)+1), "%s%s\n",paramhilo->ruta,arg1.direccion);
  printf("Protocolo: %s\n",arg1.protocolo );
  printf("Version: %s\n",arg1.version );
  printf("Extension: %s\n",arg1.extension );
  printf("Archivo: %s\n", ruta);


  fd= open(ruta, O_RDONLY);
  if (fd>0) {
    printf("Archivo abierto\n");
    write(sd,"HTTP/1.1 200 OK\r\n",16);
  }else{
    perror("open");
    write(sd,"HTTP/1.1 404 Not Found\r\n\r\n",strlen("HTTP/1.1 404 Not Found\r\n\r\n"));
    pthread_exit(NULL); //termina este hilo
  }
  if (fstat(fd,&st)!=-1){
    sprintf(input, "Content-Length: %ld\r\n",st.st_size);
    write(sd,input,strlen(input));
  }
  if (strcmp(arg1.extension, "pdf") == 0) {
    strcat(input,"Content-type: application/pdf\r\n\r\n");
  }
  if (strcmp(arg1.extension, "txt") == 0) {
    strcat(input,"Content-type: text/plain\r\n\r\n");
  }
  if (strcmp(arg1.extension, ".html") == 0) {
    strcat(input,"Content-type: text/html\r\n\r\n");
  }
  if (strcmp(arg1.extension, ".jpg") == 0 || strcmp(arg1.extension, ".jpeg") == 0) {
    strcat(input,"Content-type: image/jpeg\r\n\r\n");
  }

  //leido = read(fd, buff2, sizeof(buff2));
  write(sd,input,strlen(input));
  int sf = sendfile(sd,fd,NULL,st.st_size);
  if (sf<0){
    perror("sendfile");
  }
  write(sd,buff2,leido);
  printf("Archivo cerrado\n\n"); 
  close(fd);
  close(sd);
	//pthread_exit(NULL); //termina este hilo
  return NULL;
}

int main(int argc, char * const argv[])
{
	int fc, fd, flagp=0, opt,a=1,retorno, leido,connfc;
	char buffarg[1024],archconf[50];
  char *token="", *token2="";
  struct configuracion conf;
  struct parametros paramain;
  struct sockaddr_in procrem={}; //crea la estructura del socket(_in = internet)

  pthread_t tid;

	argumentosvacios(argc);

	while ((opt=getopt(argc,argv,"f:")) != -1){
      switch (opt) {
        case 'f':
    			strcpy(archconf,optarg);
              	flagp=1;
              	break;
       }
    }
  if (flagp==1) {
    fd = open(archconf, O_RDONLY);
    leido = read(fd, buffarg, 1024);
  }else{
    fd = open("tp5.conf", O_RDONLY);
    leido = read(fd, buffarg, 1024);
  }

  token=strtok(buffarg, "\n");
  strcpy(conf.puerto,token);
  token = strtok(NULL, "\n");
  strcpy(conf.droot,token);
  token2 = strtok(conf.puerto, "=");
  token2 = strtok(NULL, "=");
  strcpy(conf.puerto,token2);
  token2=strtok(conf.droot,"=");
  token2 = strtok(NULL, "=");
  strcpy(conf.droot,token2);
  printf("\nPuerto: %s\n",conf.puerto);
  printf("root: %s\n",conf.droot);


	fc=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
	if (fc<0){
		perror("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port= htons(atoi(conf.puerto));
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(fc, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fc,(struct sockaddr *)&procrem,sizeof (procrem))<0)
	{
		perror("bind");
		return -1;
	}
	listen(fc, 5);
	while((connfc=accept(fc, NULL, 0))>0){	//si quisiera saber la direccion y puerto del cliente debería poner una estrucura (en el segundo arg) diferente a la struck usada antes. el 3ro es el tamaño del struck, en este caso es 0
    printf("CONEXION ACEPTADA\n");
    leido=read(connfc,buffarg,sizeof buffarg);
  //  paramain = malloc(sizeof(struct parametros));
    strcpy(paramain.lectura,buffarg);
    paramain.sockete=connfc;
    strcpy(paramain.ruta,conf.droot);
    retorno = pthread_create(&tid, NULL, hilo,(void *) &paramain); //crea un hilo y le asigna una funcion
    if (retorno<0){
      printf("Error al crear el hilo\n");
    }
  }
	close(connfc);
	return 0;
}
