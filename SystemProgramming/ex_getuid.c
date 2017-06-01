#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("getpid : %d \n", getpid());
    printf("getppid : %d \n", getppid());
    printf("getuid : %d \n", getuid());
    printf("geteuid : %d \n", geteuid());
    return 0;
}
