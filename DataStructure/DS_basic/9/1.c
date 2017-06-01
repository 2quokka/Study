#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

int main(int argc, char *argv[])
{
	FILE * fp;
	char str[SIZE];

	if(argc < 2)
	{
		fprintf(stderr,"%s filename \n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if((fp = fopen(argv[1], "w"))== NULL)
	{
		fprintf(stderr,"file open fail..\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		fputs("insert string (exit '.'): ",stdout);
		fgets(str,SIZE,stdin);

		if(*str == '.')
			break;
		
		fputs(str,fp);
	}
	
	fclose(fp);
	return 0;
}
