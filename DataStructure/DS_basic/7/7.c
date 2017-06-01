#include <stdio.h>


void sort(int *num, int size);

int main(){

	int num[10] = {9,4,7,2,3,6,0,5,1,8};
	int i;

	printf("before sort : ");
	for(i=0; i<10;i++)
		printf("%d ", num[i]);
	
	puts("");

	sort(num,10);

	printf("after sort : ");
	for(i=0; i<10; i++)
		printf("%d ", num[i]);

	puts("");

	return 0;
}

//buble sort
void sort(int *num, int size)
{
	int i,j, tmp;

	for(i=0;i < size; i++)
	{
		for(j=0; j < size-i-1 ; j++)
		{
			if(num[j] > num[j+1])
			{
				tmp = num[j];
				num[j] = num[j+1];
				num[j+1] = tmp;
			}
		}
	}
}
