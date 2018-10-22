#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "tp4.h"

void argumentosvacios(int argc){
  if (argc==1) {
    printf("\n...Se tomara el puerto 5000 por default...\n\n ");
  }
}

struct argumentos {
    char direccion[40];
    char barra[40];
    char palabra[40];
};

int main(int argc, char * const argv[])
{
	int fc,fe, leido, conectado2, connfc, pid,flagp=0, opt,a=1, puerto;
	char buff[8192], buff2[8192], mensaje[500], buscar[100], z[200];
  struct argumentos arg1;

	struct sockaddr_in procrem={}; //crea la estructura del socket(_in = internet)

	argumentosvacios(argc);

	while ((opt=getopt(argc,argv,"p:")) != -1){
      switch (opt) {
        case 'p':
    			puerto=*optarg;
              	flagp=1;
              	break;
       }
    }

	fc=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
	if (fc<0){
		perror("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	if (flagp==1){
		procrem.sin_port= htons(puerto);
	}else{
		procrem.sin_port= htons(5000);
	}
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(fc, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fc,(struct sockaddr *)&procrem,sizeof procrem)<0)
	{
		perror("bind");
		return -1;
	}
	listen(fc, 5);
	signal(SIGCHLD,SIG_IGN); //para sacar procesos terminados de la PCB
	while((connfc=accept(fc, NULL, 0))>0){	//si quisiera saber la direccion y puerto del cliente debería poner una estrucura (en el segundo arg) diferente a la struck usada antes. el 3ro es el tamaño del struck, en este caso es 0
		pid=fork();

		//HIJO
		if (pid==0){
			while ((leido=read(connfc,buff,sizeof buff))>0){
				printf("Mensaje recibido: %s\n", buff);
				arg1=obtenerargumentos(buff);

				struct sockaddr_in serverhttp={};

				fe=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
				if (fe<0){
					perror("socket");
					return -1;
				}
				serverhttp.sin_family = AF_INET;
				serverhttp.sin_port= htons(80);
				struct hostent *hp = gethostbyname((char *)arg1.direccion);
				inet_pton(AF_INET,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0])), &serverhttp.sin_addr); //convierte el binario de addr_list a string y lo copia a un buffer (&server...)
				setsockopt(fe, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
				conectado2 = connect(fe,(struct sockaddr *)&serverhttp, sizeof serverhttp);
				if  (conectado2 < 0 ){
			        perror ("connect");
	                return -1;
				}
				sprintf(mensaje, "GET /%s HTTP/1.0\nHost: %s\nConnection: close\n\n",arg1.barra, arg1.direccion);
				write(fe, mensaje, sizeof mensaje);
				while ((leido = read(fe, buff2 , sizeof buff2)) > 0){
					if  (leido < 0 ){
						perror ("read");
						return -1;
					}
          strcpy(buscar,arg1.palabra);
					strcpy(z,parse(buff2, buscar));
					write(connfc,z,strlen(z));
				}
			}
			return 0;
		}
		close(connfc);
	}
	return 0;
}
