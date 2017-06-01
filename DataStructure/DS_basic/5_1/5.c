#include <stdio.h>

#define SIZE 12

typedef unsigned char Bool;
#define True 1
#define False 0

int main(){
	int num[SIZE], fq[SIZE]={0};
	int i, j, max=0;
	Bool redundancy_check = False;
//	int max_index=0;
	
	for(i=0; i<SIZE; i++)
	{
		printf("insert number(1-10) [%d/%d] : ",i+1, SIZE);
		scanf("%d", &num[i]);
		/*
		if(num[i] <1 || num[i] > 10)
		{
			printf("1 - 10 number please ! \n");
			i--;
		}
		*/
	}

	//frequency check

	for(i=0; i < SIZE; i++)
	{
		for(j=0; j < SIZE; j++)
		{
			if(num[i] == num[j])
				fq[i]++;
		}
	}

	for(i=0;i < SIZE; i++)
	{
		if(max < fq[i])
		{
			max = fq[i];
	//		max_index = i;
		}
	}

	printf("high frequency number : ");

	for(i=0;i< SIZE; i++)
	{
		redundancy_check = False;

		for(j=0;j<i-1; j++)
			if(num[i] == num [j])
				redundancy_check = True;

		if(fq[i] >= max && !redundancy_check)
			printf(" %d", num[i]);
	}
/*
	for(i=0;i< SIZE; i++)
	{
		if(max == fq[i])
			printf(" %d", i);
	}
*/
	puts("");
	//printf("high frequency number : %d \n", num[max_index]);

	return 0;
}
