#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    int fd1, fd2, fd3;
    int i, end;

    char buf;


    if(argc !=4 ){
        fprintf(stdout, "%s file oddfile evenfile\n", argv[0]);
        exit(1);
    }

    if((fd1 = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "%s not found!", argv[1]);
        exit(2);
    }

    if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0){
        fprintf(stderr, "%s can not creat!", argv[2]);
        close(fd1);
        exit(2);
    }

    if((fd3 = open(argv[3], O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0){
        fprintf(stderr, "%s can not creat!", argv[3]);
        close(fd1);
        close(fd2);
        exit(2);
    }


    i = 0;
    end = lseek(fd1, 0, SEEK_END);
    while(1){
        printf("%d\n", i);
        if(lseek(fd1, i, SEEK_SET) == end)
            break;

        read(fd1, &buf, 1);
        write(fd2, &buf, 1);
        i++;

        if(lseek(fd1, i, SEEK_SET) ==end)
            break;

        read(fd1, &buf, 1);
        write(fd3, &buf, 1);
        i++;
    }

    close(fd1);
    close(fd2);
    close(fd3);
    
    return 0;
}
