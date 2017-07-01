#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

void main(){
    printf("tok : 0x%x \n ", ftok("/home/gmldms/",'a'));
}
