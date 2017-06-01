#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf[BUFSIZ];

    if( argc < 2)
    {
        fprintf(stderr, "Usage : %s filename \n",argv[0]);
        exit(-1);
    }

    if(( fd = open(argv[1], O_RDONLY)) == -1)
    {
        perror(argv[1]);
        exit(-2);
    }

    while( read(fd, buf, BUFSIZ) > 0)
       fputs(buf, stdout);


    close(fd);
    return 0;
}
