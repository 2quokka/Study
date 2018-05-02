#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int fd;
    char buf;
    char srrMessage[] = "sorry file can't read";

    if((fd = open(argv[1], O_RDONLY)) == -1){
        write(1, srrMessage, strlen(srrMessage));
        return 0;
    }

    while(read(fd, &buf, 1)>0)
    {
        write(1, &buf, 1);
    }

    close(fd);

    return 0;
}
