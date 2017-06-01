#include <stdio.h>
#include <string.h>

int main(void)
{
	char fname[128];
	char buffer[256];
	FILE *fp;
	int line_num=0;

	fputs("파일 이름을 입력하시오 : ", stdout);
	fgets(fname,50,stdin);
	fname[strlen(fname)-1] = '\0';

	fp = fopen(fname,"r");

	while( fgets(buffer, 256, fp) != NULL)
	{
		printf("     %d: ", ++line_num);
		fputs(buffer,stdout);
	}

	fclose(fp);

	return 0;
}
