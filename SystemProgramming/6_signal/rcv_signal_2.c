#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define LIMIT_TIME 20

void main() {
    int rand_num=getpid();

    srand((unsigned int)rand_num);
    rand_num %= LIMIT_TIME;
    printf("[Child] : sleep random number: %d\n", rand_num);
    sleep(rand_num);

    printf("[Child] process terminate!\n");
    exit(0);
}
