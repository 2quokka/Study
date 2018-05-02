#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    int fd;
    char buf;

    if(argc < 3){
        fprintf(stdout, "Usage : %s filename mode(odd, even)\n", argv[0]);
        return 0;
    }

    if((fd = open(argv[1], O_RDONLY))<0){
        perror("file can't find");
        return -1;
    }

    if(strcmp(argv[2], "odd"))
        lseek(fd, 1, SEEK_SET);
    else if(strcmp(argv[2], "even"))
        lseek(fd, 0, SEEK_SET);
    else{
        fprintf(stdout, "%s is not mode...", argv[2]);
        close(fd);
        return -1;
    }

    while(read(fd, &buf, 1) > 0)
    {
        write(1, &buf, 1);
        lseek(fd, 1, SEEK_CUR);
    }

    close(fd);
    return 0;
}
