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
#include <signal.h>

void argumentos(int argc){
  if (argc==1) {
    printf("\n...SE DEBEN INGRESAR ARGUMENTOS...\n\n ");
    exit(0);
  }
}

void  ALARMhandler(int sig)
{
  exit(0);
}

int main(int argc, char * const argv[]){

	int fd, leido, conectado, opt, flagp=0,flagh=0, a=1, puerto;
	char buff[1024], dominio[50], output[20], mensaje[100], host[10];

	struct sockaddr_in procrem={};
  signal(SIGALRM, ALARMhandler);

	argumentos(argc);

    while ((opt=getopt(argc,argv,"u:t:p:h:")) != -1){
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
        case 'h':
          strcpy(host,optarg);
                flagh=1;
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

  if (flagh==1) {
    inet_pton(AF_INET,host, &procrem.sin_addr);
  }else{
    inet_pton(AF_INET,"127.0.0.1", &procrem.sin_addr);
  }

  conectado = connect(fd,(struct sockaddr *)&procrem,sizeof procrem);
	if (conectado < 0)
	{
		perror("connect");
		return -1;
	}
  sprintf(mensaje, "%s %s", dominio,output); // GET /p=%s&b=%s
  alarm(3);
	write(fd, mensaje, strlen(mensaje));
  printf("Resultado de la busqueda...\n\n");
  while ((leido = read(fd, buff , sizeof buff))>0) {
    if  (leido < 0 ){
      perror ("read");
      return -1;
    }
    write(1,buff,leido);
    printf("\n\n");

	return 0;
  }
}
