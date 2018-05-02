#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
    int i, fd;
    fd = open("tmp.txt", O_RDONLY);
    read(fd, &i, 4);
    printf("i=[%d]\n", i);
    close(fd);
}
