#include <stdio.h>

int main(void)
{
	int a[5]= {4,2,3,0,1};
	int b[5];
	int i,j;
	int min= a[0];

	for(i=0;i<5;i++)
	{
		min = a[i];
		for(j=i; j<5; j++)
		{
			min = (min > a[j]) ? a[j] : min ;
		}
		b[i] = min;
	}
	return 0;
}
