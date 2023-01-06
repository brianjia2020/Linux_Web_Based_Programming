#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

/**
 * socket: create a socket
 * domain: AF_INET, AF_LOCAL
 * type: 
 *   SOCK_STREAM for tcp 
 *   SOCK_DGRAM for udp
 * protocol: 0 -> automatic
 * return a file descriptor
*/

/**
 * bind: bind socket with a fixed ip and port
 *     struct sockaddr
*/

// client code 
int main(int argc, char* argsv[]) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    inet_pton(AF_INET, "196.127.168.1", &server_addr.sin_addr.s_addr);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) perror("");
    while(1) {
        char buf[128] = "";
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = 0;
        sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        char read_buf[128] = "";
        recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("read buf is: %s\n", read_buf);
    }
    printf("%d\n", fd);
}

