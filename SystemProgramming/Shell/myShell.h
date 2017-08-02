// myshell.h

#include <stdio.h>
#include <string.h> // strlen ..
#include <sys/types.h> //fork ...
#include <unistd.h>  // fork.. exec.. 
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h> //wait..
#include <signal.h>

#define COMMAND_BUFFER 1024
#define MAX_PATH 256
#define MAX_TOKEN 256
#define MAX_COMMAND 50

//type
#define NL 0
#define RD_R 1
#define RD_L 2
#define RD 3
#define PP 4
#define BG 8

typedef struct COMMAND_{
    char *tok[MAX_TOKEN];
    unsigned char type;
}COMMAND;

//function
int run(char *command);
int accessCheck(char *filename);
int setpath(char **path, char **cTok);
int initPath(char **path);
int tokenize(char *command, struct COMMAND_ *cmdList);
int specialCommand(char **cTok);
int execute(const struct COMMAND_ *cmd, int in, int out);
int pipeTofile(int pd, const char *fn);
int fileTopipe(const char *fn, int pd);

static char *dir_path[MAX_PATH];
static COMMAND cmdList[MAX_COMMAND];
