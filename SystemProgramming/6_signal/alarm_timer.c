#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


void sigalrm_signalhandler(int);

int pid;
extern int errno;

void main(){
    int status =0;

    if (( pid = fork() ) == -1 ) {
        perror("fork() : ");
        exit(1);
    }
    else if( pid == 0 ) {
        execl("./rcv_signal_2", "rcv_signal_2", (char *)NULL);
        perror("execl() : ");
        exit(2);
    }
    else if( pid > 0) {
        signal (SIGALRM, sigalrm_signalhandler);
        printf("[Parent] : Set Alarm Clock \n ");
        alarm(10);

        while( wait(&status) == -1 ){
            if( errno == EINTR ) {
                errno = 0;
                printf("[Parent] : Timeout!! \n");
            }
            else {
                perror("");
                break;
            }
        }
        printf("[Parent] : child process is killed by Parent\n");
    }

    printf("[Parent] : Remaining Alarm Clock : %d\n", alarm(0));
    exit(0);
}

void sigalrm_signalhandler(int sig) {
    if( sig == SIGALRM ) {
        printf("[Parent] : Send SIGKILL \n");
        kill(pid, SIGKILL);
    }
}
              
