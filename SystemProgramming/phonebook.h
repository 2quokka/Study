#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

typedef struct {
    char name [64];
    char phonenumber[20];
} PHONEBOOK;
