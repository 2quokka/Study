#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char letter[16];
    int val, base, i, temp;
    int p, r;

    if(argc < 3 )
    {
        fprintf(stderr, "%s base value", argv[0]);
        return 0;
    }

    //initialize

    for(i=0;i<10;i++)
    {
        letter[i]=i+48;
    }

    for(;i<16;i++)
    {
        letter[i]=i+55;
    }

    base = atoi(argv[1]);
    val = atoi(argv[2]);

    temp=1;
    i=0;

    while(temp <= val){
        temp = temp * base;
        i++;
    }

    while(temp > 1 )
    {
        temp = temp / base;
        p = val / temp;
        r = val % temp;
        putchar(letter[p]);
        val = r;
    }

    putchar('\n');

    return 0;
}
