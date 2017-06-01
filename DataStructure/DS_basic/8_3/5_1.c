#include <stdio.h>
#include <string.h>

void reverse(char * str);

int main(void)
{
	char str[30];
	int i,len;
	len = strlen(str);
	char tmp;
	
	printf("insert string : ");
	fgets(str,30,stdin);
	str[strlen(str)-1]='\0';

	puts(str);
	reverse(str);
	puts(str);

	return 0;
}

void reverse(char *str)
{
	int i;
	char tmp;
	int len = strlen(str);

	for(i=0; i<len/2; i++)
	{
			tmp = *(str+i);
			*(str+i) = *(str+len-i-1);
			*(str+len-i-1) = tmp;
	}

}
