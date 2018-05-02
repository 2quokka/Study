#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXLENGTH 128

int main(void){
    char buf[MAXLENGTH];
    int size=0;

    while( (size = read(0, buf, MAXLENGTH)) > 0) {
        write(1, buf, size);
    }

    exit(0);
}

