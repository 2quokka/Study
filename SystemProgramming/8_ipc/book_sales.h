#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>

typedef struct {
    char bookname[20];
    char sale_date[20];
    int left_stock;
} BOOK_SALES;
