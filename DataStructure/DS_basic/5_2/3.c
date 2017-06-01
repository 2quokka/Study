#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256
int main(void)
{
    char str1[SIZE]="It is Useful Where a statement Is needed sYntactically, but no action is reQUired";
    char str2[SIZE];

    int i, len;


	//printf("len = %d\n", len);

	//strcpy(str2, str1);

    for(i=0;i<strlen(str1) ;i++)
    {
		if(islower(str1[i]))
	    	str2[i]=toupper(str1[i]);
		else if(isupper(str1[i]))
	    	str2[i]=tolower(str1[i]);
		else
			str2[i]=str1[i];
    }
	
	for(i=0; str2[i] != '\0' ; i++)
		putchar(str2[i]);
  

    puts("");

    return 0;
}
