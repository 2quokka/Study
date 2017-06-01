#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(){
    int pid, ret;
    int i;
    int status;

    pid = fork();

    if (pid == 0)
    {
        fprintf(stderr,"child process running .. \n");
        //while(1){}
        exit(1);
    }
    if(pid > 0)
    {
        printf("parent wait ...\n");
        //kill(pid, SIGINT);
        //printf("send SIGINT signal !! \n ");
        ret = wait(&status);
        printf("ret : %d \n", ret);
        printf("status  : 0x%x\n", status);
        /*
        for(i = 31 ; i = 0 ; i--)
        {
            printf("%d",(status >> i) & 1);
        }
        */

        printf("\nexit code  : 0x%x \n", status>>8);
        printf("siganal 8 bit : 0x%x \n", 0xFF & status);
    }

    return 0;
}

