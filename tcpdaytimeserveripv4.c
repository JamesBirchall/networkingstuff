#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv){

  int listeningfiledescriptor, connectionfiledescriptor;
  struct sockaddr_in serveraddress;
  char buffer[1000];
  time_t ticks;

  if ( (listeningfiledescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("socket error\n");
  }

  memset(&serveraddress, 0, sizeof(serveraddress));

  serveraddress.sin_family = AF_INET;
  serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddress.sin_port = htons(6666);

  if ( (bind(listeningfiledescriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress))) < 0 ){
    printf("bind error\n");
  }

  if ( (listen(listeningfiledescriptor, 1024)) < 0){
    printf("listen error\n");
  }

  for( ; ; ){
    connectionfiledescriptor = accept(listeningfiledescriptor, (struct sockaddr*) NULL, NULL);

    ticks = time(NULL);
    snprintf(buffer, sizeof(buffer), "%.24s\r\nby Birchall timekeeping, bye!\n", ctime(&ticks));
    
    if((write(connectionfiledescriptor, buffer, strlen(buffer))) < 0){
      printf("write error\n");
    } else{
      printf("time sent to remote client!\n");
    }
    
    close(connectionfiledescriptor);
  }

  return 0;
}
