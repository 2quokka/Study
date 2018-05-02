#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    execl("/bin/ps", "wow", (char*)0);
    while(1);
    return 0;
}
