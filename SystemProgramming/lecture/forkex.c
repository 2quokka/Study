#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    if(fork() == 0)
        printf ("child. pid = %d ppid=%d\n", getpid(), getppid());
    else
        printf("parent. pid = %d ppid=%d\n", getpid(), getppid());

    printf("both");

    return 0;
}
