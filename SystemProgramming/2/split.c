#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1, fd2, fd3;
    char ch;
    long i = 0;

    if( argc < 4)
    {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(-1);
    }
    
    
    if( (fd1 = open(argv[1], O_RDONLY)) < 0 )
    {
        perror(argv[1]);
        exit(-2);
    }

    if( (fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644)) < 0 )
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

    while( lseek(fd1, i, SEEK_SET) != -1 )
    {
        if( read(fd1, &ch, 1) > 0 )
        {
            if( i % 2 == 0)
                write(fd2, &ch, 1);
            else
                write(fd3, &ch, 1);
        }
        else
            break;

          i++;
    }

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
