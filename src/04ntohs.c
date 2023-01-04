#include <stdio.h>
#include <arpa/inet.h>

/**
 * web to system conversion
*/
int main(int argc, char* argv[]) {
    short a = 0x0102; //xiao duan
    short b = htons(a);

    printf("%x\n", ntohs(b));
    return 0;
}