#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#define BIGNUM 10000000

int main(int argc, char *argv[]){

    char ch, f, l;
    int pid, i;

    if((pid=fork()) > 0){ //parent
        f = 'A'; l = 'Z';
    }
    else if(pid==0){ //child
        f = 'a'; l = 'z';
    }

    else{
        perror(argv[0]);
        exit(1);
    }

    for(ch=f; ch<=l; ch++){
        for(i=0; i<BIGNUM;i++);
        write(1,&ch,1);
    }

    if(pid >0)
        wait(0);

    write(1, "\n", 1);

    exit(0);

    return 0;
}
