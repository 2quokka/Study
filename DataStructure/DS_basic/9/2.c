#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
	int count =1;
	FILE *fp;
	char buffer[BUFFER_SIZE];

	if(argc < 3)
	{
		fprintf(stderr, "%s File Search-String \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if((fp=fopen(argv[1], "r"))==NULL)
	{
		fprintf(stderr,"File open fail.. \n");
		exit(EXIT_FAILURE);
	}

	while(fgets(buffer, BUFFER_SIZE, fp))
	{
		if(strstr(buffer,argv[2]))
			printf("%d : find string ! \n" , count);
	}

	fclose(fp);
	return 0;
}
