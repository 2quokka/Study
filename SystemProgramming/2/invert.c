#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char ch;

    if(argc < 3)
    {
        fprintf(stderr,"[Message] %s file1 file2 \n");
        exit(-1);
    }

    if( (fd1 = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(-2);
    }

    if( (fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror(argv[1]);
        close(fd1);
        exit(-3);
    }

    lseek(fd1, -2, SEEK_END);
    
    while(read(fd1, &ch, 1))
    {
        printf("%c ", ch);
        write(fd2, &ch, 1);
        if( (lseek(fd1, -2, SEEK_CUR)) == -1)
            break;
    }
    
    close(fd1);
    close(fd2);


    return 0;
}
