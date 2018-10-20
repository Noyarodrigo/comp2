#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{	
	int fd, leido, conectado;
	char buff[1024];
	struct sockaddr_in procrem={};
	{};
	fd=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
	if (fd<0)
	{
		perror("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port= htons(80);
	inet_pton(AF_INET,"192.168.1.123", &procrem.sin_addr);
	conectado = connect(fd,(struct sockaddr *)&procrem,sizeof procrem);
	if (conectado < 0)
	{
		perror("connect");
		return -1;
	}
	char comando[]="GET /es/ua/fi.html HTTP/1.1\n\n"; //agregar \n Host: www.um.edu.ar\nConnection: close \n\n",67);
	write(fd,(void *)comando,sizeof dir);
	while ((leido=read(fd,buff, sizeof buff))>0){
		if (leido<0)
		{
			perror("read");
			return -1;	
		}
		write(1,buff,leido);
	}
	return 0;
}