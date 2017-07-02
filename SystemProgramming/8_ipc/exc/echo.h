#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSIZE 128

#define SERVER_TYPE 10L
#define CLIENT_TYPE 90L
#define PATH_NAME "/tmp"
#define NUMTRIES 3

typedef struct { 
    long mtype;
    char mdata[MAXSIZE];
} MSG_BUF;

