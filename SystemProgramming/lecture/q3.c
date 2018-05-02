#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(void){
    int i=4836483, fd;
    char ibuf[128];

    fd = open("tmp.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    sprintf(ibuf, "%d", i);
    write(fd, ibuf,strlen(ibuf));
    close(fd);
}
