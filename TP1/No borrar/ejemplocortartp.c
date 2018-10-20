#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
  int fdo,fdd,leido;
  char buff[50];
  //hay que cambiar los 50 bits por los argumentos yagregar un while como el otro
  //ejemplo para que lea hasta que no haya nada que leer
  fdo=open("creaciondeprocesos.c",O_RDONLY);

  fdd=open("dest1",O_CREAT|O_RDWR,0666);
  leido=read(fdo,buff,50);
  write(fdd,buff,leido);
  close(fdd);

  fdd=open("dest2",O_CREAT|O_RDWR,0666);
  leido=read(fdo,buff,50);
  write(fdd,buff,leido);
  close(fdd);

  fdd=open("dest3",O_CREAT|O_RDWR,0666);
  leido=read(fdo,buff,50);
  write(fdd,buff,leido);
  close(fdd);
  close(fdo);
  return 0;
}
