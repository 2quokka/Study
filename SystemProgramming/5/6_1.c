#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

    

void sigint_signalhandler (int);
void sigquit_signalhandler (int);

int sig_count = 0;

int main(void){
    signal(SIGINT, sigint_signalhandler);
    signal(SIGQUIT, sigquit_signalhandler);

    while(1){}
    
    return  0;
}

void sigint_signalhandler (int sig){

    printf("control c pressed \n");
    sig_count++;

}

void sigquit_signalhandler (int sig){

    printf("control c count %d \n", sig_count);
    exit(1);
}
    
