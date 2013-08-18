#include <stdio.h>
#include <string.h> //memset function
//#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> //addrinfo struct nad function
#include <arpa/inet.h> //inet_ntop and other network byte functions
#include <netinet/in.h> //IPSTRLEN defines

int main(int argc, char *argv[]){

  struct addrinfo hints, *res, *p;
  int status;
  char ipstring[INET6_ADDRSTRLEN];

  if(argc != 2)
    fprintf(stderr, "usage: %s hostname\n", argv[0]);

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if((status = getaddrinfo(argv[1],NULL, &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2bind
  }

  printf("IP address for %s:\n\n", argv[1]);

  for(p = res; p != NULL; p = p->ai_next){
    void *addr;
    char *ipver;

    //get pointer to the addres itself
    //different fields in IPv4 and IPv6
    if(p->ai_family == AF_INET){
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else{
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    //convert the IP to a string and print
    inet_ntop(p->ai_family, addr, ipstring, sizeof ipstring);

    printf(" %s: %s\n", ipver, ipstring);
  }

  freeaddrinfo(res);  //free linked list

  return 0;
}
