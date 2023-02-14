#include <stdio.h>
#include <arpa/inet.h>

void tftp_download(char* argv) {
  int fd;
  unsigned short p_num = 0;
  unsigned char cmd = 0;
  char cmd_buf[512] = "";
  char recv_buf[516] = "";
  struct sockaddr_in client_addr;
  socklen_t cliaddr_len = sizeof(client_addr);

  if (dest_addr.sin_port == 0) {
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(69);
    puts("send to IP:");
    fgets(recv_buf, sizeof(recv_buf), stdin);
    *(strchr(recv_buf,'\n')) = '\0';
    inet_pton(AF_INET, recv_buf, &dest_addr.sin_addr);
  }

  int len = sprintf(cmd_buf, "%c%c%s%c%s%c", 0, 1, argv, 0, "octet", 0);
  sendto(sockfd, cmd_buf, len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
  fd = open(argv, O_WRONLY|O_CREAT, 0666);
  if (fd < 0) {
    perror("open error");
    close(sockfd);
    exit(-1);
  }
  return 0;
}