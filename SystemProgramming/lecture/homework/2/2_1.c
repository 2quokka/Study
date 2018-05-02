#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    int fd1, fd2;
    char buf;

    if(argc !=3 ){
        fprintf(stdout, "%s file1 file2\n", argv[0]);
        exit(1);
    }

    if((fd1 = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "%s not found!", argv[1]);
        exit(2);
    }

    if((fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0){
        fprintf(stderr, "%s can not creat!", argv[1]);
        close(fd1);
        exit(2);
    }

    lseek(fd1, -2, SEEK_END);

    while(1){
        read(fd1, &buf, 1);
        write(fd2, &buf, 1);

        if(lseek(fd1, -2, SEEK_CUR)==0){
            read(fd1, &buf, 1);
            write(fd2, &buf, 1);
            buf = '\n';
            write(fd2,&buf, 1);
            break;
        }
    }

    close(fd1);
    close(fd2);
    
    return 0;
}
