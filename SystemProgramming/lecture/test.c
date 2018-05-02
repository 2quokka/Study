#include <stdio.h>

int main(void) {
    char ch;
    ch = 0x13;
    printf("[%d]\n", ch); //19

    ch = 012;
    printf("[%d]\n", ch); //10

    return 0;
    }
