#include <stdio.h>

int main()
{
	int i;
	char a;

	for(i=1; i<1001; i++)
	{
		if(i % 7 ==0)
			printf("%d\n", i);

		if(i % 100 ==0)
		{
			printf("Continue (y/n) ?");
			a=getchar();
			getchar();
			if(a != 'y')
				break;
		}
	}
	return 0;
}
