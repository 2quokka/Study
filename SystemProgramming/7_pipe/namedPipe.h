#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PUBLIC "Public"
#define LINESIZE 512
#define NUMTRIES 3

struct message{
    char privfifo[15];
    char filename[100];
};

