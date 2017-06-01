#include <stdio.h>

int main()
{
	int num[5] = {1, 2, 3, 4, 5};
	int sum=0, avg, i;

	for(i=0; i<5; i++)
	{
		sum += *(num +i);
	}

	avg = sum / 5;

	printf("sum : %d \t avg : %d\n",sum,avg);
	return 0;
}
