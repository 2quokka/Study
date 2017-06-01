#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256
int main(void)
{
    char str1[SIZE];
    char str2[SIZE];

    int i, len;

	while(1)
	{
		printf("insert string : ");	
		scanf("%s", str1);

		if(strcmp(str1,"q") == 0 || strcmp(str1,"Q") ==0)
			break;
    	
		len = strlen(str1);

   		strcpy(str2,str1);

    for(i=0;i<len;i++)
    {
		if(islower(*(str2+i)))
	    	*(str2+i)=toupper(*(str2+i));
	
		else if(isupper(*(str2+i)))
	    	*(str2+i)=tolower(*(str2+i));
    }

    i=0;

    while(*(str2+i)!=0)
    {
		putchar(*(str2+i));
		i++;
    }

    	puts("");
	}
    return 0;
}
