#include <stdio.h>
#include <string.h>

void changeChar(char *str, char *ptr)
{
	int i;
	if(!strcmp(ptr, "even"))
		i=0;
	else if(!strcmp(ptr, "odd"))
		i=1;
	
	while(str[i] != '\0')
	{
		str[i] = 'X';
		i+=2;
	}
}

int main(void)
{
	char str[512];
	strcpy(str, "Hello, World");
	puts(str);
	changeChar(str, "even");
	puts(str);
	strcpy(str, "Hello, World");
	changeChar(str, "odd");
	puts(str);
	return 0;
}
