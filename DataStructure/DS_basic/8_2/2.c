#include <stdio.h>

int main()
{
	int a=5;
	int b=-5;
	printf(" %d >> 1 = %d \n", b, b >> 1);
	printf(" %d >> 1 = %d \n", a, a >> 1);
	printf(" %d >> 2 = %d \n", a, a >> 2);
	printf(" %d >> 3 = %d \n", a, a >> 3);


	printf(" %d << 1 = %d \n", a, a << 1);
	printf(" %d << 2 = %d \n", a, a << 2);
	printf(" %d << 3 = %d \n", a, a << 3);

	return 0;
}
