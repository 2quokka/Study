#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int status;

    if(fork()==0)
    {
        execv("/bin/cat", argv);
        exit(127);
    }

    wait(&status);

    printf(" child exit code : %d \n", status >> 8);

        return 0;
}
