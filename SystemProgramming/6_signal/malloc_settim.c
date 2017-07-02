#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_COUNT 100

void sigalrm_signalhandler(int sig);

int mian(void){

    struct itimerval t_val_start, t_val_end;
    char *p;
    int i =0;

    t_val_start.it_value.tv_sec = 5L;
    t_val_start.it_value.tv_usec = 0L;

    t_val_start.it_interval.tv_sec = 5L;
    t_val_start.it_interval.tv_usec = 0L;

    setitimer(ITIMER_REAL, &t_val_start, NULL);
    p = malloc(64);
    getitimer(ITIMER_REAL, &t_val_end);

    printf("sec : %ld, usec : %ld \n", t_val_end.it_value.tv_sec, t_val_end.it_value.tv_usec);


    return 0;
}
void sigalrm_signalhandler(int sig){
}
    
