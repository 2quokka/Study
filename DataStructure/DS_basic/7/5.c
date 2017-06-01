#include <stdio.h>

int sum(int *, int);

int main(){
	int num[5] = {1, 2, 3, 4, 5};

	printf("result : %d\n",sum(num, 5));
	return 0;
}

int sum(int * num, int size)
{
	int i, sum=0;
	for(i=0;i<size;i++)
	{
		sum+=num[i];
	}
	return sum;
}
