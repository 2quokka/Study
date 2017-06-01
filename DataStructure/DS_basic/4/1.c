#include <stdio.h>

int main(){

	int i=1, n;
	int result =0;
	printf("number ? "); scanf("%d", &n);

// for 문과 while 문 
/*
	for(; i<n+1 ; i++)
		result += i;

	while(i<n+1)
	{
		result +=i;
		i++;
	}
*/
	do
	{
		result += i;
		i++;
	}
	while(i<n+1);

	printf("from 1 to %d sum result : %d \n", n, result);
	return 0;
}
