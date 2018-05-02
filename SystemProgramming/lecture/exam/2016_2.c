#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct {
    char name[20];
    int years;
}PP;

int main(int argc, char *argv[])
{
    int fd, size;
    PP tmp;
    char buf[10];

    if(argc < 2)
    {
        fprintf(stderr, "%s filename \n", argv[0]);
        exit(-1);
    }

    if((fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, 0640) < 0))
    {
        perror("open fail!!");
        exit(-1);
    }

    while(1)
    {
        memset(&tmp, 0x00, sizeof(PP));
        if((size = read(0, tmp.name, sizeof(tmp.name))) < 0)
            break;
        
        tmp.name[size-1] = 0;

        if((size = read(0, buf, sizeof(buf))) < 0)
            break;

        buf[size-1]= 0;

        tmp.years=atoi(buf);

        if((size = write(fd, (char *)&tmp, sizeof(tmp)))< 0)
            printf("write fail\n");
    }

    close(fd);
    return 0;

}
