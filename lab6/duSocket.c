#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "duSocket.h"

int setupServer(int portno){
  //socket pointer
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0){
    fprintf(stderr, "Error opening socket\n");
    exit(0);
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(portno);

  if(bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
    printf("Error on binding\n");
    exit(1);
  }

  listen(sockfd, 5);
  return sockfd;
}

int callServer(char* host, int portno){
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0){
    fprintf(stderr, "Error opening socket\n");
    exit(0);
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  
  struct hostent *server;
  server = gethostbyname(host);
  
  if (server == NULL){
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }
  
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  
  if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
    printf("ERROR connecting\n");
    exit(0);
  }
  
  return sockfd;
}
  
int serverSocketAccept(int serverSocket){
  
  int newsockfd;
  
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr);
  
  int sockfd = serverSocket;
  printf("waiting for a call...\n");
  newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
  printf("Connected\n");
  
  if(newsockfd < 0){
    printf("ERROR on accept");
    exit(1);
  }
  return newsockfd;
}

void writeInt(int x, int socket){
  int newsockfd = socket;
  int n = write(newsockfd, &x, sizeof(int));
  
  if (n < 0){
    printf("ERROR writing to socket\n");
    exit(1);
  }
}

int readInt(int socket){
  int newsockfd = socket;
  
  int buffer;
  int n = read(newsockfd, &buffer, sizeof(int));
  
  if(n<0){
    printf("ERROR reading from socket\n");
    exit(1);
  }
  
  return buffer;
}
