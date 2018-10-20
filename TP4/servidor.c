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

void argumentosvacios(int argc){
  if (argc==1) {
    printf("\n...Se tomara el puerto 5000 por default...\n\n ");
  }
}

char * obtenerargumentos(char buff){
	char *token="", delim[]=" ", aux[1024];
	static char * argumentos[2];
	int i=0;
	strcpy(aux,(char *)&buff);
  	token=strtok(aux, delim);
  	while (token != NULL){
		argumentos[i]=token;
		i++;
		token = strtok(NULL, delim);
	}
	printf("Pagina:%s\n",argumentos[0]);
	printf("Palabra:%s\n",argumentos[1]);
   return argumentos;
}

int parse(char * buff2, char palabra){
    int x,z=0;
    char *token="";
    char delim[] = " ,;:.-_<>\n";
    token=strtok(buff2, delim);
	while (token != NULL){
		x=strcmp(token,&palabra);
          if (x==0){
            z=1;
          }
	    token = strtok(NULL, delim);
	}
    return z;
}

int main(int argc, char * const argv[])
{
	int fc,fe, leido, conectado2, connfc, pid,z,flagp=0, opt,a=1,i=0, puerto;
	char buff[1024], buff2[1024], argumentos[2],mensaje[100],delim[]=" ",*token="";

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
				argumentos=obtenerargumentos(*buff);
				//strcpy(argumentos,obtenerargumentos(*buff));
				token=strtok(buff, delim);
			  	/*while (token != NULL){
					argumentos[i]=token;
					i++;
					token = strtok(NULL, delim);
				}*/
				printf("\nPagina: %s\n",argumentos[0]);
				printf("Valor a buscar: %s\n",argumentos[1]);

				struct sockaddr_in serverhttp={};

				fe=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
				if (fe<0){
					perror("socket");
					return -1;
				}
				serverhttp.sin_family = AF_INET;
				serverhttp.sin_port= htons(80);
				struct hostent *hp = gethostbyname((char *)argumentos[0]);
				inet_pton(AF_INET,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0])), &serverhttp.sin_addr); //convierte el binario de addr_list a string y lo copia a un buffer (&server...)
				setsockopt(fe, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
				conectado2 = connect(fe,(struct sockaddr *)&serverhttp, sizeof serverhttp);
				if  (conectado2 < 0 ){
			        perror ("connect");
	                return -1;
				}
				sprintf(mensaje, "GET / HTTP/1.0\nHost: %s\nConnection: close\n\n", argumentos[0]);
				printf("Enviando\n\n");
				write(fe, mensaje, sizeof mensaje);
				while ((leido = read(fe, buff2 , sizeof buff2)) > 0){
					if  (leido < 0 ){
						perror ("read");
						return -1;
					}
					write(1,buff2,leido);
					z=parse(buff2, *argumentos[1]);
					if (z==1){
						write(connfc,"\nLa palabra ingresada fue encontrada en la pagina\n",49);
					}else{
						write(connfc,"\nLa palabra ingresada NO fue encontrada en la pagina\n",52);
					}
				}
			}
			return 0;
		}
		close(connfc);
	}
	return 0;
}
