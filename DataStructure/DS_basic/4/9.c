#include <stdio.h>

int main()
{
	int i;
	for(i=1; i<101; i++)
	{
		if(i % 2 !=0)  //짝수가 아니라면 
			continue;

		printf("%d\n",i);
	}

	return 0;
}
