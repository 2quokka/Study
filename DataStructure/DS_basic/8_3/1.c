#include <stdio.h>
#include <string.h>

int myStrlen(char *str)
{
	int i=0;
	while(*str)
	{
		i++; str++;
	}
	return i;
}

int main()
{
	char str[128] = "Hello, My name is Seung Chan";

	puts(str);
	printf("myStrlen result = %d \n", myStrlen(str));
	printf("strlen result d= %d \n", strlen(str));
	return 0;
}
