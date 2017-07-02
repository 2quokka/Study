#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

clock_t malloc_time(int size);
int main(){

    char *p;
    int f = 64, i;

    for(i = 0; i < 6 ; i ++){
        printf("malloc : %d \n ", f << i);
        printf("second : %f \n ", ((float)malloc_time(f << i))/CLOCKS_PER_SEC);
    }

    return 0;
}

clock_t malloc_time(int size){
    char *p;

    clock_t t =clock();

    p = malloc(size);

    t = clock() - t;

    free(p);

    return t;
}
