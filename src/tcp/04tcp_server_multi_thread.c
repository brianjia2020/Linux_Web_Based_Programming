#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct {
  int cfd;
  struct sockaddr_in client;
} INFO;

void* resq_client(void* arg) {
  INFO* info = (INFO*)arg;
  char ip[16] = "";
  printf(
    "client ip=%s, port=%d\n", 
    inet_ntop(AF_INET, &(info->client.sin_addr.s_addr), ip, 16), 
    ntohs(info->client.sin_port));
  
  while(1) {
    char buf[1024] = "";
    int n = read(info->cfd, buf, sizeof(buf));
    if (n == 0) {
      printf("client closed.\n");
      break;
    }
    printf("%s\n", buf);
    write(info->cfd, buf, n);
  }
  close(info->cfd);
  free(info);
  return NULL;
};

int main(int argc, char const *argv[])
{
  /* code */
  int lfd = socket(AF_INET, SOCK_STREAM, 0);
  if (lfd < 0) 
    perror("socket create failed.");
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(8888);
  myaddr.sin_addr.s_addr = 0;

  if(bind(lfd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0)
    perror("bind unsuccessfully.");
  listen(lfd, 128);

  // loop to read/write
  while(1) {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int cfd = accept(lfd, (struct sockaddr*)&client_addr, &len);

    // allocate a space for info before creating a thread for the incoming client
    INFO* info = malloc(sizeof(INFO));
    info->cfd = cfd;
    info->client = client_addr;

    pthread_t pthid;
    pthread_create(&pthid, NULL, resq_client, info);
    pthread_detach(pthid);
  }
  return 0;
}

/**
 * first handshake: SYN -> 1 means request for connection.
 * second handshake: SYN,ACK -> 1 means acknowledgement from server
 * third handshake: ACK -> 1, client to server acknowledgement
*/
