#include <stdio.h>

void myEnc(char *str)
{
	while(*str)
	{
		*str = (*str)+3;
		str++;
	}
}
void myDec(char *str)
{
	while(*str)
	{
		*str = (*str)-3;
		str++;
	}
}
int main()
{
	char str[128];
	printf("insert string : ");
	scanf("%s", str);

	myEnc(str);
	printf("Encrypt : %s \n", str);
	myDec(str);
	printf("Decrypt : %s \n", str);
	return 0;
}
