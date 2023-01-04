#include <stdio.h>
#include <arpa/inet.h>

/**
 * convert ip address of string to proper 4 byte int
 * AF_INET -> ipv4
 * AF_INET6 -> ipv6
 * 
 * src 
*/
int main(int argc, char* argv[]) {
    const char* ip = "192.168.1.2";
    uint32_t dst;
    if(inet_pton(AF_INET, ip, &dst)) {
        printf("Success!\n");
    }

    printf("%d\n", dst);

    // manually do this
    unsigned char* p = (unsigned char*)&dst; // take first 4 bits
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3)); // 192 168 1 2

    // C provided the function
    char ipToShow[INET_ADDRSTRLEN];
    if(inet_ntop(AF_INET, &dst, ipToShow, INET_ADDRSTRLEN)) {
        printf("Success!\n");
        printf("ip=%s\n", ipToShow);
    }
}