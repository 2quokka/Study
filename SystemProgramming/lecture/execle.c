#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    static char *new_envp[] = {"USER=TESTER", "HOME=/TEST_DIR", "TESTSTRING=execle()test"};
    printf ("execle() test program!!\n");
    execle ("./default_envp", "new_pgm", "p1", "p2", (char *)NULL, new_envp);
}

