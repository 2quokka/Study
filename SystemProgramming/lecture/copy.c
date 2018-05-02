#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define MAXLENGTH 256

int copyfile (char *fn1, char *fn2);

int main(int argc, char *argv[]){
    if(argc <3 ){
        fprintf(stderr, "Usage: %s in_file out_file\n", argv[0]);
        exit(-1);
    }

    copyfile(argv[1], argv[2]);
    return 0;
}

int copyfile (char *fn1, char *fn2){
    char buf[MAXLENGTH];
    int fd1, fd2;
    int size=0;

    if((fd1 = open(fn1, O_RDONLY)) == -1){
        perror("file can't open ! ");
        return(-1);
    }

    if((fd2 = open(fn2, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1){
        perror("file can't open ! ");
        close(fd1);
        return(-1);
    }

   // memset(buf, 0x00, sizeof(buf));

    while((size = read(fd1, buf, MAXLENGTH))>0){
        write(fd2, buf, size);
    }

    return 0;
}

