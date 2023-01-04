#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int num = 0x01020304; //xiao duan
    int sum = htonl(num); // transform to da duan
    printf("num=%d, sum=%d\n", num, sum);
    // unsigned int a =  ntohl();

    short a = 0x0102;
    int b = htonl(a);
    printf("a=%d, b=%d\n", a, b);
    printf("%x\n", ntohl(b));
    return 0;
}