#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void){
    int fd, len;
    char buf[512];

    if((fd=open("/dev/tty",O_RDONLY | O_NDELAY))<0){
        perror("open");
        exit(-1);
    }

    sleep(5);

    if((len = read(fd, buf, 512))>0){
        buf[len-1] = 0;
        printf("[%d]:[%s]\n", len, buf);
    }
    else
        printf("No input/\n");

        return 0;
}
