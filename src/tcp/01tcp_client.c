#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9999

int main(int argc, char const *argv[])
{
  // create socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0)
    perror("Socket client creation failed.");
  // connect to server
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT); // server port
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  int status = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (status < 0)
    perror("Connect failed!");
  // send and recv data
  while(1) {
    char buf[128] = "";
    char r_buf[128] = "";
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf)-1] = 0;
    write(sock_fd, buf, strlen(buf));
    int count = read(sock_fd, r_buf, strlen(r_buf));
    if (count == 0) {
      printf("server closed!");
      break;
    }
    printf("received from server %s\n", r_buf);
  }
  // close socket
  close(sock_fd);
  return 0;
}
