#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ptr=NULL;
	printf("before malloc : %d \n", ptr);
    ptr= malloc(3);
    printf("after malloc : %d \n", ptr);
    free(ptr);
    printf("after free : %d \n", ptr);

	return 0;
}
