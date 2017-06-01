#include <stdio.h>
#include <string.h>

int findChar(char *str, char ch)  //strstr
{
	int index=0;
	while(*(str))
	{
		if(*(str) == ch)
			return index;
		index++;
		str++;
	}
	
	return -1;
}

int main()
{
	char * str = "Hello, World";
	char * str1 = "World";
	char ch= 'o';

	printf("findChar(%s, %c)= %d \n",str, ch, findChar(str,ch));
	printf("strstr(%s, %s) = %s \n",str, str1, strstr(str,str1));
	return 0;
}
