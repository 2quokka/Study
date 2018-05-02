#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int addval;
    int in, out;
    char ch;

    if(argc < 3)
    {
        fprintf( stderr, "%s infile addvalue outfile \n", argv[0]);
        return 0;
    }

    if((in = open(argv[1], O_RDONLY))<0)
    {
        perror("sorry, file not open ");
        exit(-1);
    }

    if((out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
    {
        perror("sorry, file not open ");
        exit(-1);
    }

    ch +=2;
    while(read(in, &ch, 1)>0)
        write(out, &ch, 1);

    close(in);
    close(out);
    return 0;
}
