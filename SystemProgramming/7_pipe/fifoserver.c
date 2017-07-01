#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "MYFIFO"

int main(void)
{
    FILE *fp;
    char readbuf[80];

    umask(0);
    mknod(FIFO_FILE, S_IFIFO |0666, 0);

    while(1)
    {
        fp = fopen(FIFO_FILE, "r");
        fgets(readbuf, 80, fp);
        printf("Received string : %s \n", readbuf );
        fclose(fp);
    }

    return 0;
}
