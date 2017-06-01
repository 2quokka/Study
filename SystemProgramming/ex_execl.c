#include <stdio.h>
#include <unistd.h>

int main(){
    printf("execl() test program!!! \n");
    execl("./default_envp", "new_program", "param_1", "param_2", (char *)NULL);
    perror("execl() :");
    return 0;
}
