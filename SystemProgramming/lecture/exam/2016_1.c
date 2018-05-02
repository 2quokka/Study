#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define MAX 100

int main(int argc, char* argv[])
{
    int fd, count=0, i;
    char ch;
    char buf[MAX];

    if(argc < 3)
    {
        fprintf(stderr, "[Usage] : %s filename letter \n", argv[0]);
        return 0;
    }

    if((fd = open(argv[1], O_RDONLY)) < 0)
    {
        perror("sorry file not found\n");
        exit(-1);
    }

    memset(buf, 0, MAX);

    printf(" MAX : %d\n", MAX);
    i=0;
    while(read(fd, &ch, 1) > 0)
    {
        if(ch != ' ' && ch != '\n')
        {
            buf[i++] = ch;
            printf(" ch : %c \t i : %d \n", ch, i);
        }
        else // space and enter
        {
            buf[i] = '\0';

            if(strcmp(buf, argv[2]) == 0) //equal
                count++;

            i=0;
            memset(buf, 0, MAX);
        }
    }

    printf("count : %d i : %d \n", count, i);

    return 0;
}
