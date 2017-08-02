#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    char str[]={'c','u','t', 0,'-', 'd', 0, 0, ' ', 0, 0, '-', 'f', '2', 0, 'l', 's', '.', 't', 'x', 't', 0,};
    char *pt[10] = {str, &str[4], &str[8], &str[11], &str[15], NULL};
    char *path = "/usr/bin/cut";

//    execl(path, "cut", "-d", " ", "-f", "2", "ls.txt", NULL);
    execv(path, pt);
    return 0;
}

