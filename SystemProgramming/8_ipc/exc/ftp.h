#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>

#define MAXSIZE 128;
#define KEY_PATH "/tmp"

#define INVALID 1
#define REQUESTED 2
#define PROCESSED 3
#define NAME_SIZE 128
#define DATA_SIZE 1024

typedef struct{
    char filename[NAME_SIZE];
    int status;
    char data[DATA_SIZE];
}SHM_FRM;
