#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 1

int main(int argc, char *argv[])
{
	FILE *ifp, *ofp;
	int count;
	unsigned char buffer[SIZE];

	if(argc < 2)
	{
		fprintf(stderr,"%s file-name \n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if((ifp=fopen(argv[1], "rb"))==NULL)
	{
		fprintf(stderr, "%s : File open fail.. \n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if((ofp=fopen(argv[2], "wb"))==NULL)
	{
		fprintf(stderr, "%s : File open fail.. \n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	while(count= fread(buffer,sizeof(unsigned char),SIZE,ifp ) > 0)
	{
		fwrite(buffer, sizeof(unsigned char), count, ofp);
	}

	fclose(ifp);
	fclose(ofp);
	return 0;
}
