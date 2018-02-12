#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080

void handle_request(int sockid) {
  int lenread, bufferlen = 1024;
  char buffer[1024] = {0};

  lenread = read(sockid, buffer, bufferlen);
  printf("%s\n", buffer);
  send(sockid, "test hello", 10, 0);
}

void *apilistener() {
  struct sockaddr_in addr;
  int sockid, newsockid, sockopt, addr_size;
  // May try UDP in the future - requires the use of ACK packets
  if ((sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
    perror("could not create socket");
    exit(1);
  }

  sockopt = 1;
  if(setsockopt(sockid, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &sockopt, sizeof(sockopt))) {
    perror("setting socket options");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr_size = sizeof(addr);
  // ip address should be configurable parameter/pulled from system
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  if (bind(sockid, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind failed");
    exit(1);
  }

  if(listen(sockid, 10) < 0) {
    perror("listen");
    exit(1);
  }
  
  while (1) {
    if ((newsockid = accept(sockid, (struct sockaddr*)&addr, (socklen_t*)&addr_size)) < 0) {
      perror("accept");
      exit(1);
    }

    if (!fork()) { // this is the child
      close(sockid);
      handle_request(newsockid);
      close(sockid);
      exit(0);
    }
  }

  return NULL;
}

int main(int argc, char **argv) {
  pthread_t tid;
  pthread_create(&tid, NULL, apilistener, NULL);
  pthread_exit(NULL);
  printf("hello, world\n");
}
