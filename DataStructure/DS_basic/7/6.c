#include <stdio.h>

void sum(int *i, int *j, int *ret);

int main(){

	int i,j,result;

	printf("insert number 2 : ");
	scanf("%d %d",&i, &j);

	sum(&i,&j,&result);

	printf("result : %d \n", result);
	return 0;
}

void sum(int *i, int *j, int *ret)
{
	*ret = *i + *j;
}
