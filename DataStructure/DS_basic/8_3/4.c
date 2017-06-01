#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int deleteChar(char *str, char ch)
{
	int find =0;
	while(*(str))
	{
		if(*(str) == ch)
			find =1;

		if(find)
			*(str) = *(str+1);
		str++;
	}

	if(!find)
		return -1;
	else
		return 0;
}

int main()
{
	char str[128]= "hello World";
	char ch;

	puts(str);
	printf("insert del object : ");
	ch=getchar();

	if(deleteChar(str, ch)==-1)
	{
		fprintf(stderr,"sorry not found \n");
		exit(EXIT_FAILURE);
	}
	
	printf("result = %s \n", str);

	return 0;
}
