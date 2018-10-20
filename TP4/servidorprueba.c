#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

void conexion(int leido, char buff[]){
	int fd, leido, conectado;
	char buff[1024];
	struct sockaddr_in procrem={};
	{
		
	};
	fd=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
	if (fd<0)
	{
		perror("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port= htons(80);
	inet_pton(AF_INET,"200.51.41.139", &procrem.sin_addr);
	conectado = connect(fd,(struct sockaddr *)&procrem,sizeof procrem);
	if (conectado < 0)
	{
		perror("connect");
		return -1;
	}
	char dir[]="GET /es/ua/fi.html HTTP/1.1\n\n";
	write(fd,(void *)dir,sizeof dir);
	while ((leido=read(fd,buff, sizeof buff))>0){
		if (leido<0)
		{
			perror("read");
			return -1;	
		}
		write(1,buff,leido);
	}
}

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
	inet_pton(AF_INET,"192.168.2.167", &procrem.sin_addr);
	setsockopt(fd, SOL_SOCKET,SO_REUSEADDR,NULL,0);//para poder reutilizar el puerto inmediatamente
	if (bind(fd,(struct sockaddr *)&procrem,sizeof procrem)<0)
	{
		perror("bind");
		return -1;
	}
	listen(fd, 5);
	signal(SIGCHLD,SIG_IGN); //para sacar procesos terminados de la PCB
	connfd=accept(fd, NULL, 0);	//si quisiera saber la direccion y puerto del cliente debería poner una estrucura (en el segundo arg) diferente a la struck usada antes. el 3ro es el tamaño del struck, en este caso es 0
	pid=fork();
	//HIJO
	if (pid==0){
		while ((leido=read(connfd,buff,sizeof buff))>0){
			conexion(leido,buff);
			/*write(1, buff, leido);
			write(connfd,buff,leido);*/
		}	
		return 0;	
	}
	close(connfd);
	return 0;
}