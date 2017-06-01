#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int ch; //fgetc return int ( EOF)

	if(argc < 2)
	{
		fprintf(stderr,"%s file-name \n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if((fp=fopen(argv[1], "r"))==NULL)
	{
		fprintf(stderr, "File open fail.. \n");
		exit(EXIT_FAILURE);
	}

	while((ch= fgetc(fp)) != EOF)
		putchar(ch);

	fclose(fp);
	return 0;
}
