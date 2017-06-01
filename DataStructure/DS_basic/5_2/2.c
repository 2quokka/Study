#include <stdio.h>

int main()
{
    char str1[] = "It is useful Where a statement Is needed sYntactically, but no action is reQUired";
    char str2[100];
    int i=0, j=0;

    while(str1[i] != '\0')
    {
		if(str1[i] ==' ')
		{
	    	i++;
	    	continue;
		}

		str2[j++]=str1[i++];
    }

    str2[j] = '\0';

    puts(str2);

    return 0;
}
