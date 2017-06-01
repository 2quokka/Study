#include <stdio.h>

void reverse(char *str)
{
	char tmp[128];
	int len=0, i;

	while(*(str+len))  //len 
		len++;
	
	for(i= len; i>0; i--)
	{
		*(tmp+(len-i)) = *(str+i-1); 
	}
	*(tmp+len) = '\0';

	for(i=0; i<len; i++)
	{
		*(str+i) = *(tmp + i);
	}
		
}
int main()
{
	char str[128];
	
	printf("insert string :");
	scanf("%s", str);

	reverse(str);

	puts(str);

	return 0;
}
