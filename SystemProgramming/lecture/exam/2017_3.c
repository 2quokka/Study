#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int i;
    char exc[] = "/usr/bin/cmp";
    char *buf[10];


    if (argc < 4)
    {
        fprintf(stderr, "[Usage] : %s pname file1 file2 option\n", argv[0]);
        return(0);
    }

    if(fork() == 0) // child
    {
        execv(exc, &argv[1]);
        exit(-1);
    }

    else // parent
    {
        wait((int *)0);
        fprintf(stderr, "child exited\n");
    }

    return 0;
}
