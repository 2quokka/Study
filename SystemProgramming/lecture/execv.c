#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    char *new_argv[]={"diffName", "p1", "p2", (char*)NULL};
    execv("./default_envp", new_argv);
    perror("execv() :");

    exit(0);
    return 0;
}
