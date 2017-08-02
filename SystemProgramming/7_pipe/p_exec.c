	
//You need to close the pipe fds in the parent, or the child won't receive EOF, because the pipe's still open for writing in the parent. This would cause the second wait() to hang. Works for me:

#include <unistd.h>
#include <stdlib.h>


int main()
{
        int des_p[2];
        if(pipe(des_p) == -1) {
          perror("Pipe failed");
          exit(1);
        }

        if(fork() == 0)            //first fork
        {
            close(STDOUT_FILENO);  //closing stdout
            dup(des_p[1]);         //replacing stdout with pipe write 
            close(des_p[0]);       //closing pipe read
            close(des_p[1]);

            //const char* prog1[] = { "ls", "-l", 0};
            //execvp(prog1[0], prog1);
            execl("/bin/ls", "ls", "-l", 0);
            perror("execvp of ls failed");
            exit(1);
        }

        if(fork() == 0)            //creating 2nd child
        {
            close(STDIN_FILENO);   //closing stdin
            dup(des_p[0]);         //replacing stdin with pipe read
            close(des_p[1]);       //closing pipe write
            close(des_p[0]);

            //const char* prog2[] = { "grep", "p_", 0};
            //execvp(prog2[0], prog2);
            execl("/bin/grep", "grep", "p_", 0);
            perror("execvp of wc failed");
            exit(1);
        }

        close(des_p[0]);
        close(des_p[1]);
        wait(0);
        wait(0);
        return 0;
}
