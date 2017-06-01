#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    int status, pid;

    if( (pid = fork()) == -1) {
        perror ("fork() : ");
        exit(-1);
    }

    if( pid == 0 ) {
        execl("/usr/bin/ls", "ls", "-l", (char *)NULL);

        perror("execl() : ");
        exit(0);
    }
    else {
        wait(&status);
        if((status >> 8) == 0)
            printf("correct exit\n");
        else
            printf("wrong exit \n exit code : %d \n", (status >> 8) );
    }

    return 0;
}
