#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

void main(int argc, char* argv) { 
  int sock_fd = 0;
  char buf[1024] = "";
  unsigned short port = 8000;
  struct sockaddr_in send_addr;

  bzero(&send_addr, sizeof(send_addr));
  send_addr.sin_family = AF_INET;
  send_addr.sin_port = htons(port);

  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fd < 0) {
    perror("socket failed");
    close(sock_fd);
    exit(1);
  }

  if (argc > 1) {
    // assigning ip address
    send_addr.sin_addr.s_addr = inetaddr(argv[1]);
  } else {
    perror("have no ip address");
    exit(1);
  }

  int yes = 1;

  // SO_BROADCAST is to grant authorization
  setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
  strcpy(buf, "Broadcast Success!");

  int len = sendto(sock_fd, buf, strlen(buf), 0, (struct sockaddr *)&send_addr, sizeof(send_addr));
  if (len < 0) {
    printf("Send Error");
    close(sock_fd);
    exit(1);
  }
  return 0;
}