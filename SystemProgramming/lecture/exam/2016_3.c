#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buf[512];
    int fd, count;
    if((fd=open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666)) <0)
        exit(-1);

    close(1);
    dup(fd);
    close(fd);

    while( (count=read(0, buf, 512)) > 0 )
    {
        buf[count] = 0;
        printf("%s", buf);
    }

    return 0;
}
