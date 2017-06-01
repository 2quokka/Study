#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	char ch;
	FILE *fpr, *fpw;

	if((fpr=fopen("test.txt", "r")) == NULL)
	{
		fprintf(stderr,"file open failed \n");
		exit(1);
	}
	if((fpw=fopen("cp.txt", "w")) == NULL)
	{
		fprintf(stderr,"file open failed \n");
		exit(1);
	}

	while((ch=fgetc(fpr)) != EOF)
		fputc(ch,fpw);
		
	fclose(fpr);
	fclose(fpw);
	return 0;
}
