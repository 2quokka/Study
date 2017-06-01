#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
	FILE *fp1, *fp2;
	char str[128];
	char buffer[256];
	char *ptr = NULL;
	int i;

	char * word1 = "Android";
	char * word2 = "안드로이드";

	fp1=fopen("test.txt","r");
	fp2=fopen("out.txt", "w");

	while(fgets(buffer,256,fp1) != NULL)
	{
		ptr= buffer;
		while(*ptr)
		{
			for(i=0; !isspace(*ptr) ; ptr++, i++)
			{
				str[i]= *ptr;
			}
			str[i]= '\0';

			if(!strcmp(str,word1))
			{
				fputs(word2,fp2);
			}
			else
			{
				fputs(str,fp2);
			}
			fputs(" ",fp2);
			ptr++;
		}
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
