#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
  int fdo,fdd,leido;
  char buff[50];
  //hay que cambiar los 50 bits por los argumentos yagregar un while como el otro
  //ejemplo para que lea hasta que no haya nada que leer
  fdd=open("unido.txt",O_RDWR|O_CREAT);

  fdo=open("dest1",O_RDONLY,0666);
  leido=read(fdo,buff,50);
  write(fdd,buff,leido);
  close(fdo);

  fdo=open("dest2",O_RDONLY);
  leido=read(fdo,buff,50);
  write(fdd,buff,leido);
  close(fdo);

  fdo=open("dest3",O_RDONLY);
  leido=read(fdo,buff,50);
  write(fdd,buff,leido);
  close(fdo);

  close(fdd);
  return 0;
}
