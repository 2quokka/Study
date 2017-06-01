#include <stdio.h>
#define SIZE 10

int main(void)
{
    int arr[SIZE];
    int i, max, min;

    for(i=0; i< SIZE; i++)
    {
        printf("input number %d /%d :", i+1, SIZE);  //입력개수 확인
		scanf("%d",&arr[i]);
    }

    max=arr[0]; min=arr[0]; //초기값 으로 지정


    for(i=0; i<SIZE; i++)
    {
		if(max < arr[i])
		    max= arr[i];

		if(min > arr[i])
	 	   min= arr[i];
    }

    printf("max = %d, min = %d \n", max, min);
    return 0;
}
