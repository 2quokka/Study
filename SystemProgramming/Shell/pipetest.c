#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){

    int A_pfd[2];
    int B_pfd[2];

    pipe(A_pfd);
    pipe(B_pfd);

    if(fork()==0){
        close(1);
        dup(A_pfd[1]);
        close(A_pfd[1]);
        close(A_pfd[0]);
        execl("/bin/ls", "ls", "-l",(char *)0);
    }
    sleep(1);

    if(fork()==0)
    {
        close(0);
        dup(A_pfd[0]);
        close(1);
        dup(B_pfd[1]);

        close(A_pfd[0]);
        close(A_pfd[1]);
        close(B_pfd[0]);
        close(B_pfd[1]);

        execl("/bin/grep", "grep", "test", (char *)0);
    }
    sleep(1);

    if(fork() == 0)
    {
        close(0);
        dup(B_pfd[0]);

        close(A_pfd[0]);
        close(A_pfd[1]);
        close(B_pfd[0]);
        close(B_pfd[1]);

        execl("/usr/bin/wc", "wc", 0);
    }

    //close(pfd[0]);
    close(B_pfd[1]);
    close(A_pfd[1]);
    wait(0);
    wait(0);
    wait(0);
    return 0;
}
