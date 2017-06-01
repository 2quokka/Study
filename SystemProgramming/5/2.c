#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    int status, pid;

    if( argc < 2)
    {
        fprintf(stderr, "Usage : %s filename \n",argv[0]);
        exit(-1);
    }

    if( (pid = fork()) == -1) {
        perror ("fork() : ");
        exit(-2);
    }

    if( pid == 0 ) {
        execl("./mycat", "mycat", argv[1], (char *)NULL);

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
