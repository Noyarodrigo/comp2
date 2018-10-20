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
	{
		
	};
	fd=socket(AF_INET, SOCK_STREAM,0); //creo socket ipv4 on su respectivo descriptor
	if (fd<0)
	{
		perror("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port= htons(5000);
	//procrem.sin_addr.s_addr = 192.168.1.52;
	//procrem.sin_addr.s_addr = htonl(0xc0a80134);
	//inet_pton(AF_INET,"192.168.14.28", &procrem.sin_addr);
	inet_pton(AF_INET,"192.168.2.167", &procrem.sin_addr);
	conectado = connect(fd,(struct sockaddr *)&procrem,sizeof procrem);
	if (conectado < 0)
	{
		perror("connect");
		return -1;
	}
	write(fd,"GET /es/ua/fi.html HTTP/1.0\n",7);
	leido=read(fd,buff, sizeof buff);
	if (leido<0)
	{
		perror("read");
		return -1;	
	}
	write(1,buff,leido);
	return 0;
}