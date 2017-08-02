#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char text[80];

void read2line(char *input){
    while(1) {
        read(0, input, 1);
        if(*input == '\n')
            break;
        else
            input++;
    }
}

void main(int argc, char **argv){
    int fd[2];
    if(pipe(fd) == -1){
        perror(argv[0]);
        exit(1);
    }
    if(fork()==0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        printf("ls display sorted\n");
        fflush(stdout);
        execl("/bin/ls","ls","-l",(char*)0);
        exit(127);
    }
    if(fork()==0){
        close(0);
        dup(fd[0]);
        close(fd[0]);
        //read2line(text);
        printf("\tHeading: %s\n", text);
        fflush(stdout);

        execl("/bin/sort","sort","-k","5,5n",(char*)0);
        exit(127);
    }
    close(fd[0]); 
    close(fd[1]);

    while(wait((int*)0) != -1 );

    exit(0);
}
