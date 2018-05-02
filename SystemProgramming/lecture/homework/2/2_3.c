#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    int fd[3];  // 0 ==even  1==odd   2== origin
    int i;

    char buf;


    if(argc !=4 ){
        fprintf(stdout, "%s evenfile oddfile origin\n", argv[0]);
        exit(1);
    }

    if((fd[0] = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "%s not found!", argv[1]);
        exit(2);
    }

    if((fd[1] = open(argv[2], O_RDONLY)) < 0){
        fprintf(stderr, "%s not found!", argv[2]);
        close(fd[0]);
        exit(2);
    }

    if((fd[2] = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0){
        fprintf(stderr, "%s can not creat!", argv[3]);
        close(fd[0]);
        close(fd[1]);
        exit(2);
    }

    for(i=0;;i++){
        if(read(fd[i%2], &buf, 1)>0)
            write(fd[2], &buf, 1);
        else
            break;
    }

    close(fd[0]);
    close(fd[1]);
    close(fd[2]);
    
    return 0;
}
