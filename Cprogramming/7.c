#include <stdio.h>
#include <string.h>

int main(void)
{
	char fname[128];
	char buffer[256];
	FILE *fp;

	fputs("파일 이름을 입력하시오 : ", stdout);
	fgets(fname,50,stdin);
	fname[strlen(fname)-1] = '\0';

	fp = fopen(fname,"w");

	while(strcmp(buffer," \n")){
		fgets(buffer, 256, stdin);
		fputs(buffer, fp);
	}

	fclose(fp);

	return 0;
}
