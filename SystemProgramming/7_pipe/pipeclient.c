//pipeclient.c

#include "namedPipe.h"

int main(int argc, char *argv[]){

    int fd_cont, fdpub, n;
    char line[LINESIZE];

    if(argc < 2)
    {
        printf("MSEEAGE : insert file name ! \n");
        exit(1);
    }

    if((fdpub = open(PUBLIC, O_WRONLY)) == -1 ){
        perror(PUBLIC); //close
        exit(2);
    }
    else
        printf("[client] pub open ! \n ");

    if((fd_cont = open(argv[1], O_RDONLY)) == -1)
    {
        perror(argv[1]);
        exit(1);
    }
    else
        printf("[client] %s open !  \n", argv[1]);
    


    while((n = read(fd_cont, line, LINESIZE)) > 0 ){
        printf("[client]line:  %s \n", line);
        write(fdpub, line, n);
    }

    close(fd_cont);

    return 0;
}
