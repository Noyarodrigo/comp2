
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(){
	//0:stdin, 1:stdout, 2:stderr
	char buffer[1024]="";
  char nombre[20]="";
  int leido;
  int i;
	int fd = open("minuscula.txt", O_CREAT|O_RDWR, 0660);
  int name= read(0,&nombre , sizeof nombre);
	while((leido = read(fd, &buffer, sizeof buffer)) > 0)
	{
    for (i = 0; i < leido; i++) {
      buffer[i]=toupper(buffer[i]);
      }
      int fe=open(namecal, O_CREAT|O_RDWR|O_TRUNC, 0660);
      write(fe,&buffer,leido);
	}
	return 0;
}
