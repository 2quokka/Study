#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    int fd;

    fd = open ("qaz", O_RDWR|O_TRUNC| O_CREAT, 0666);

    lseek(fd, 10L, SEEK_END);
    write(fd, "This", 4);

    close(fd);
}
