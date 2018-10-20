#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

int main(int argc, char const *argv[])
{	
	int fd, leido, conectado,connfd, pid;
	char buff[1024];
	struct sockaddr_in procrem={}; //crea la estructura del socket(_in = internet)
	{
	};

	fd=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
	if (fd<0)
	{
		perror("socket");
		return -1;
	}
	
	procrem.sin_family = AF_INET;
	procrem.sin_port= htons(8080); //host to network short, cambia de formato host a red
	//procrem.sin_addr.s_addr = 192.168.1.52;
	//procrem.sin_addr.s_addr = htonl(0xc0a80134);
	inet_pton(AF_INET,"192.168.14.28", &procrem.sin_addr);
	setsockopt(fd, SOL_SOCKET,SO_REUSEADDR,&a,sizeof a);//para poder reutilizar el puerto inmediatamente
	if (bind(fd,(struct sockaddr *)&procrem,sizeof procrem)<0)
	{
		perror("bind");
		return -1;
	}
	listen(fd, 5);
	signal(SIGCHLD,SIG_IGN); //para sacar procesos terminados de la PCB
	while((connfd=accept(fd, NULL, 0))>0){	//si quisiera saber la direccion y puerto del cliente debería poner una estrucura (en el segundo arg) diferente a la struck usada antes. el 3ro es el tamaño del struck, en este caso es 0
		pid=fork();

		//HIJO
		if (pid==0){
			while ((leido=read(connfd,buff,sizeof buff))>0){
				write(1, buff, leido);
				write(connfd,buff,leido);
			}	
			return 0;	
		}
		close(connfd);
	}
	return 0;
}