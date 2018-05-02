#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int status;
    

    if(fork()==0){
        printf("one pid = %d \n", getpid());
        exit(1);
    }
    if(fork()==0){
        printf("two pid = %d \n", getpid());
        exit(2);
    }
    if(fork()==0){
        printf("three pid = %d \n", getpid());
        exit(3);
    }

    while(wait(&status) != -1)
        printf("0x%x\n", status);

    printf("Parent exit!\n");

    return 0;
}
