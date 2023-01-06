#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(int argc, char** argv) {
  // for(int i = 0; i < argc; i++) {
  //   char* arg = argv[i];
  //   printf("This is the %dth arg, %s\n", i, arg);
  // }

  // 1. create socket
  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd < 0) {
    printf("Socket has not been created successfully.\n");
    return 0;
  }

  // 2. bind
  struct sockaddr_in addr; // server address
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9000);
  // inet_pton(AF_INET, "192.168.1.2", &addr.sin_addr.s_addr);
  addr.sin_addr.s_addr = INADDR_ANY;
  
  int status = bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr));
  if (status < 0) {
    printf("Binding failed.\n");
    return 0;
  }

  struct sockaddr_in client_addr; // client address info
  socklen_t len = sizeof(client_addr);
  while(1) {
    char buf[128] = "";
    recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &len);
    printf("%s\n", buf);

    // send back whatever received
    sendto(socket_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &len);
  }

  close(socket_fd);
  return 0;
}