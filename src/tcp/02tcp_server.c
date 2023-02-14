#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define MAX_TCP_CONNECTIONS 128

// Driver function
int main()
{
    // 1. create a socket
    int s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd < 0) {
        perror("server socket didn't start successfully.");
    }
    //2. bind
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(9999);
    myaddr.sin_addr.s_addr = 0; // local ip bind
    bind(s_fd, (struct sockaddr*)&myaddr, sizeof(myaddr));
    //3. listen, 
    //   make socket to passive and create two streams
    //   s_fd, backlog -> max numbers of tcp connections of the two streams
    if(listen(s_fd, MAX_TCP_CONNECTIONS) < 0) {
        perror("listen failed.");
    }
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);
    int cfd = accept(s_fd, (struct sockaddr*)&cli_addr, &len);
    if (cfd < 0) {
        perror("accept failed.");
    }
    char ip[INET_ADDRSTRLEN] = "";
    printf(
        "client ip=%s, port=%d\n", 
        inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, ip, INET_ADDRSTRLEN),
        ntohs(cli_addr.sin_port));

    // read/write
    while(1) {
        char buf[256] = "";
        int ret = read(cfd, buf, sizeof(buf));
        if (ret == 0) {
            printf("client closed.\n");
            break;
        }
        printf("received from client %s\n", buf);
        write(cfd, buf, strlen(buf));
    }

    close(cfd);
    close(s_fd);
    return 0;
}