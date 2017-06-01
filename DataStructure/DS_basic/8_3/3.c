#include <stdio.h>
#include <stdlib.h>

int myStrlen(char *str)
{
	int i=0;
	while(*str)
	{
		i++; str++;
	}
	return i;
}

int changeChar(char *str, int i, char ch)
{
	if(myStrlen(str) <= i) // i 가 문자열의 길이보다 큰경우
		return -1;

	*(str+i) = ch;
	return 0;
}

int main()
{
	int index;
	char ch;
	char str[128] = "Hello World";
	
	puts(str);
	printf("index number : ");
	scanf("%d", &index);
	getchar();
	printf("change Char : ");
	ch = getchar();

	if(changeChar(str,index,ch) == -1)
	{
		fprintf(stderr,"string length exceed \n");
		exit(EXIT_FAILURE);   // EXIT_FAILURE ==1 
	}

	printf("result = %s \n", str);

	return 0;
}
