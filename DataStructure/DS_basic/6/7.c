#include <stdio.h>
#include <stdlib.h>  //atoi

int main(int argc, char *argv[]){
	
	int i, num;

	if(argc < 2)
	{
		printf("message : %s integer_number\n", argv[0]);
		return 0;
	}

	for(i=1;i<argc; i++)
	{
		num=atoi(argv[i]);
		printf("%X  ",num);
	}

	puts("");
	return 0;
}
