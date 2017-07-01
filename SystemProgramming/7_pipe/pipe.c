#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 20

int main(int argc, char *argv[]){
    int fd[2], pid;
    static char msgout[MSGSIZE] = "\nHello, world\n";
    static char msgin[MSGSIZE];

    printf("fd[0] = %d, fd[1] = %d \n", fd[0], fd[1]);

    if(pipe(fd) == -1) {
        perror(argv[0]);
        exit(1);
    }

    printf("fd[0] = %d, fd[1] = %d \n", fd[0], fd[1]);

    if((pid = fork()) > 0) { // parent
        printf("parent pid = %d \n ", getpid());
        write(fd[1], msgout, MSGSIZE);
    }

    else if(pid == 0) {
        read(fd[0], msgin, MSGSIZE);
        printf("child pid = %d \n ", getpid());
        puts(msgin);
    }
    else {
        perror(argv[0]);
        exit(2);
    }
    exit(0);
}
