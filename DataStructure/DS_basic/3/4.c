#include <stdio.h>

int main(void)
{
	int num;

	printf("number :");
	scanf("%d", &num);

	if(num %2 ==0)
		printf("even!\n");
	else
		printf("odd!\n");

	return 0;
}
