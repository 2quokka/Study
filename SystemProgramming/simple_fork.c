#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid =0, ppid =0;

    if( (pid = fork()) == -1) {
        perror ("fork() : ");
        exit(-1);
    }

    if( pid == 0 ) {
        pid = getpid();
        ppid = getppid();
        printf("\tProcess ID:%d, \tParent Process ID: %d\n", pid, ppid);
        exit(0);
    }
    else {
        pid = getpid();
        ppid = getppid();
        printf("Process ID: %d, \tParent Process ID : %d\n", pid, ppid);
        wait((int*)0);
    }
    return 0;
}
