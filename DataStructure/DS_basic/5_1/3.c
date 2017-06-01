#include <stdio.h>
#define SIZE 10
#define MIN 0
#define MAX 1000

//bubble sort
void  sort(int array[], int size)
{
    int tmp;
    int i,j;
    for(i=0; i<size; i++)
    {
		for(j=0; j<size-i-1; j++)
		{
	    	if(array[j]<array[j+1])
	    	{
				tmp =array[j];
				array[j]=array[j+1];
				array[j+1]=tmp;
	    	}
        }
    }
}

int main(void)
{
    int i,j, tmp;
    int num[SIZE];

	//입력
    for(i=0;i<SIZE;i++)
    {
		printf("양의 정수를 입력하세요 %d/%d(단, 1000이하):",i+1,SIZE);
		scanf("%d",&tmp);
		if(tmp<0 || tmp>1000)// 예외처리
		{
	   		 printf("조건에 맞지 않습니다.\n");
	   	 	i--;
	    	continue;
		}
		else
			num[i]=tmp;
    }
    
    sort(num, SIZE);

    for(j=0;j<SIZE;j++)
		printf("%d\n",num[j]);

	return 0;
}
