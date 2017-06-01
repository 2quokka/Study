#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t pid1, pid2;

    pid1 = fork();
    pid2 = fork();

    if (pid1 == 0)
    {
        printf("child process 1\t ppid = %d \tpid = %d \n", getppid(),getpid());
        pid1 = fork();
        
        if (pid1 == 0)
            printf("child process 2\t ppid = %d \tpid = %d \n", getppid(),getpid());
        else if(pid1 > 0)
            printf("parent process, child pid = %d\n", pid1);
        else
            printf("Fork returned error code, no child\n");
    }

    if (pid2 == 0)
    {
        printf("child process 1\t ppid = %d \tpid = %d \n", getppid(),getpid());
        pid2 = fork();
        
        if (pid2 == 0)
            printf("child process 2\t ppid = %d \tpid = %d \n", getppid(),getpid());
        else if(pid2 > 0)
            printf("parent process, child pid = %d\n", pid2);
        else
            printf("Fork returned error code, no child\n");
    }

    return 0;
}
