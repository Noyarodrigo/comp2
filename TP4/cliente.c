#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

void argumentos(int argc){
  if (argc==1) {
    printf("\n...SE DEBEN INGRESAR ARGUMENTOS...\n\n ");
    exit(0);
  }
}

int main(int argc, char * const argv[]){

	int fd, leido, conectado, opt, flagp=0, a=1, puerto;
	char buff[1000], dominio[50], output[20], mensaje[100];
	
	struct sockaddr_in procrem={};
	
	argumentos(argc);

    while ((opt=getopt(argc,argv,"u:t:")) != -1){
      switch (opt) {
        case 'u':
    			strcpy(dominio, optarg);				
              	break;
        case 't':
        		strcpy(output, optarg);
              	break;
        case 'p':
    			puerto=*optarg;				
              	flagp=1;
              	break;
      }
	}

		
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	if (flagp==1){
		procrem.sin_port= htons(puerto);
	}else{
		procrem.sin_port= htons(5000);		
	}
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	inet_pton(AF_INET,"127.0.0.1", &procrem.sin_addr);
	conectado = connect(fd,(struct sockaddr *)&procrem,sizeof procrem);
	if (conectado < 0)
	{
		perror("connect");
		return -1;
	}
    sprintf(mensaje, "GET /p=%s&b=%s", dominio,output); // GET /p=www.asdjas&b=telefono
	write(fd, mensaje, strlen(mensaje));
	leido = read(fd, buff , sizeof buff);
	if  (leido < 0 ){
		perror ("read");
		return -1;
	}
	write(1,buff,leido);
	return 0;
} 