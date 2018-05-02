#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUF 256
#define MAX_PATH 256
#define MAX_COM 256
#define DEBUG

char *PATH_PTR[MAX_PATH];
int P_COUNT=0;

int initPath(char *file);
int separate(char *line, char **command);

int main(int argc, char *argv[])
{
    char line[BUF];
    char *command[MAX_COM];
    int i;

    memset( (char *)command, 0x00, sizeof(char *) * MAX_COM);

    if(initPath(".myshell") != 0 )
        fprintf(stderr, "init Path error \n");

#ifdef DEBUG
    for(i=0;i<P_COUNT;i++)
        printf("PATH_PTR[%d]= %s \n", i, PATH_PTR[i]);
#endif


    while(1)
    {
        printf("%% ");
        fgets(line, BUF, stdin);
    }

    return 0;
}

int initPath(char *file)
{
    int fd=0, i;
    char path[BUF];
    char *p;
    char ch;

    if(( fd = open(file, O_RDONLY) )== -1)
        return -1;

    i=0;
    while(read(fd, &ch, 1) > 0)
    {
        if(ch != '\n')
            path[i++] = ch;
        else
        {
            path[i] = 0;
#ifdef DEBUG
            printf("path = %s\n", path);
#endif
            if(access(path, F_OK) == 0)
            {
                p=malloc(strlen(path)+1);
                strcpy(p, path);
                PATH_PTR[P_COUNT++] = p;
            }
            i=0;
        }
    }
    close(fd);
    return 0;
}

int separate(char *line, char **command)
{
    char *p= NULL;

    p=strtok(line, " ");
    if(p != NULL)
        *command++ = p;

    while(p=strtok(NULL, " "))
    {
        command++ = 
    }
}
