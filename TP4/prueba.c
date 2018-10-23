#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

void main(){
    char palabra[]="<div style=\"float:left; margin-right:10px; margin-top:10px; display:none;\"><a href=\"http://www.facebook.com/pages/ReviUM/133816223305878\" class=\"enlaceFacebook\" target=\"_blank\"></a></div>";
    char *token="";
    char delim[] = "\n";
    char *ret;
    char* rest = str;

    token=strtok(palabra, delim);
    while (token != NULL){
      ret=strstr(token,"enlace");
        if (ret!=NULL){
          printf("%s\n",token );;
        }
      token = strtok(NULL, delim);
    }
    if (ret==NULL) {
      printf("Palabra no encontrada\n");
    }
  }
