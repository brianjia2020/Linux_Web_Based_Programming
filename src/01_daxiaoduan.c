#include <stdio.h>

typedef union std
{
    /* data */
    unsigned short a;
    unsigned char b[2];
} STD;

int main(int argc, char* argv[]) {

    STD temp;
    temp.a = 0x0102;
    if (temp.b[0] == 0x01) {
        printf("大端\n");
    } else {
        printf("小端\n");
    }
    return 0;
}