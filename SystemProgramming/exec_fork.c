#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    if(fork () == 0) {
        execl("/bin/echo", "echo" , "this is", "message one", (char *) 0);
        perror("exec one failed");
        exit(1);
    }
    if(fork() == 0) {
        execl("/bin/echo","echo","this is","message two", (char *) 0);
        perror("exec two failed");
        exit(2);
    }
    if(fork() == 0) {
        execl("/bin/echo", "echo", "this is", "message three", (char *) 0);
        exit(3);
    }
    printf("Parent program ending\n");

    return 0;
}
