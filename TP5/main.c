#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
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

void *hilo(void * buff ){
  char buff2[10000], respuesta[10240],input[30];
  int fd, leido, *con;
  struct argumentos arg1;
  struct stat st;
  arg1=obtenerargumentos(buff);
  printf("Protocolo: %s\n",arg1.protocolo );
  printf("Archivo: %s\n", arg1.direccion);
  printf("Extension: %s\n",arg1.extension );
  printf("Version: %s\n",arg1.version );
  /*if((fd=open(arg1.direccion, O_RDWR , 0666))){
    strcpy(respuesta, "HTTP/1.1 200 OK");
  }else{
    strcpy(respuesta, "HTTP/1.1 404 Not Found");
    pthread_exit(NULL); //termina este hilo
  }
  fstat(fd,&st);
  sprintf(input, "\nContent-Length: %ld",st.st_size);
  strncat(respuesta,input,strlen(input));
  if (strcmp(arg1.extension, "pdf") == 0) {
    strcat(respuesta,"\nContent-type: application/pdf\n");
  }
  if (strcmp(arg1.extension, "txt") == 0) {
    strcat(respuesta,"\nContent-type: text/plain\n");
  }
  if (strcmp(arg1.extension, ".html") == 0) {
    strcat(respuesta,"\nContent-type: text/html\n");
  }
  if (strcmp(arg1.extension, ".jpg") == 0 || strcmp(arg1.extension, ".jpeg") == 0) {
    strcat(respuesta,"\nContent-type: image/jpeg\n");
  }
  leido = read(fd, buff2, 10000);
  strncat(respuesta, buff2, leido*/
  write(1,respuesta,strlen(respuesta));
  close(fd);
	pthread_exit(NULL); //termina este hilo
}

int main(int argc, char * const argv[])
{
	int fc, fd, flagp=0, opt,a=1,retorno, leido;
	char buffarg[1024],archconf[50];
  char *token="", *token2="";
  int * connfc = malloc(sizeof(int)*1024);
  struct configuracion conf;
  pthread_t tid;

	struct sockaddr_in procrem={}; //crea la estructura del socket(_in = internet)

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
		//perror("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	//procrem.sin_port= htons(atoi(conf.puerto));
  procrem.sin_port= htons(5000);
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(fc, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fc,(struct sockaddr *)&procrem,sizeof procrem)<0)
	{
		perror("bind");
		return -1;
	}
	listen(fc, 5);
	while((connfc=accept(fc, NULL, 0))>0){	//si quisiera saber la direccion y puerto del cliente debería poner una estrucura (en el segundo arg) diferente a la struck usada antes. el 3ro es el tamaño del struck, en este caso es 0
    char buff[1024];
    printf("CONEXION ACEPTADA\n");
    leido=read(connfc,buff,sizeof buff);
    printf("%s\n",buff );
    retorno = pthread_create(&tid, NULL, hilo,(void *) buff); //crea un hilo y le asigna una funcion
    write(connfc,buff,leido);

    if (retorno<0){
      printf("Error al crear el hilo\n");
    }
  }
	close(connfc);
	return 0;
}
