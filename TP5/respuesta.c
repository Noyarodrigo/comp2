#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/sendfile.h>

struct argumentos {
    char direccion[40];
    char extension[40];
    char protocolo[40];
    char version[40];

};

void respuesta(char * extension, char * ruta,int sd){

    struct stat st;
    int fd,fe,sf;
    char input[1024], output[1024];

    fd= open(ruta, O_RDONLY);
    if (fd>0) {
        printf("\nArchivo abierto\n");
        strcpy(output,"HTTP/1.1 200 OK\r\n");
    }else{
        perror("open");
        fe= open("archivos/404.jpg", O_RDONLY);
        strcpy(output,"HTTP/1.1 404 Not Found\r\n");
        if (fstat(fe,&st)!=-1){
        sprintf(input, "Content-Length: %ld\r\n",st.st_size);
        strcat(output,input);
        }
        strcat(output,"Content-Type: image/jpeg\r\n\r\n");
        write(1,output,strlen(output)); 
        write(sd,output,strlen(output)); //envia cabecera
        int sf = sendfile(sd,fe,NULL,st.st_size); //envia archivo
        if (sf<0){
        perror("sendfile");
        }
        if (sf < st.st_size){
        printf ("faltan enviar datos\n");
        }
        close (fe);
        close (sd);
        pthread_exit(NULL); //termina este hilo
    }
    if (fstat(fd,&st)!=-1){
        sprintf(input, "Content-Length: %ld\r\n",st.st_size);
        strcat(output,input);
    }
    if (strcmp(extension, "jpg") == 0) {
        strcat(output,"Content-type: image/jpeg\r\n\r\n");
    }
    if (strcmp(extension, "jpeg") == 0){
        strcat(output,"Content-type: image/jpeg\r\n\r\n");
    }
    if (strcmp(extension, "pdf") == 0) {
        strcat(output,"Content-type: application/pdf\r\n\r\n");
    }
    if (strcmp(extension, "txt") == 0) {
        strcat(output,"Content-type: text/plain\r\n\r\n");
    }
    if (strcmp(extension, "html") == 0) {
        strcat(output,"Content-type: text/html\r\n\r\n");
    }
    if (strcmp(extension, "ico") == 0) {
        strcat(output,"Content-type: image/x-icon\r\n\r\n");
    }
    printf("\nResponse header: \n");
    write(1,output,strlen(output)); //muestra la cabecera
    write(sd,output,strlen(output)); //envia cabecera
    sf = sendfile(sd,fd,NULL,st.st_size); //envia archivo
    if (sf<0){
        perror("sendfile");
    }
    if (sf < st.st_size){
        printf ("faltan enviar datos\n");
    }
    close(fd);
    printf("\nArchivo cerrado\n"); 
    }