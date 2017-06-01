#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1, fd2, fd3, r1 = 1, r2 = 1;
    char ch;
    long i = 0;

    if( argc < 4)
    {
        fprintf(stderr, "Usage : %s filename1 filename2 filename3 \n", argv[0]);
        exit(-1);
    }
    
    
    if( (fd1 = open(argv[1], O_RDONLY)) < 0 )
    {
        perror(argv[1]);
        exit(-2);
    }

    if( (fd2 = open(argv[2], O_RDONLY)) < 0 )
    {
        perror(argv[2]);
        close(fd1);
        exit(-3);
    }
    
    if( (fd3 = open(argv[3], O_WRONLY | O_CREAT | O_EXCL , 0644)) < 0 )
    {
        perror(argv[3]);
        close(fd1);
        close(fd2);
        exit(-4);
    }

    while( (r1 > 0) || (r2 > 0) )
    {
        if( (r1 = read (fd1, &ch, 1)) > 0)
        {
            printf("%c ", ch);
            write(fd3, &ch, 1);
        }

        if( (r2 = read (fd2, &ch, 1)) > 0)
        {
            printf("%c ", ch);
            write(fd3, &ch, 1);
        }
    }

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
