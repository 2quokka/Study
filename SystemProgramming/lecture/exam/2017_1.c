#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    int i, fd;
    int from, b;
    char ch;

    if (argc < 4)
    {
        fprintf(stderr, "[Usage] %s fileName from byte character\n", argv[0]);
        return 0;
    }

    //initialize

    from = atoi(argv[2]);
    b = atoi(argv[3]);
    ch = *(argv[4]);

    printf ("from : %d \n to : %d \n ch : %c \n", from, b, ch);

    if((fd = open(argv[1], O_WRONLY )) < 0)
    {
        perror("file not found !");
        exit(-1);
    }

    lseek(fd, from, SEEK_SET);
    for(i=0; i < b; i++)
    {
        write(fd, &ch, 1);
    }

    printf("complete!!\n");
    close(fd);
    
    return 0;
}
