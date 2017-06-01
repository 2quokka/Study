#include <stdio.h>

int main()
{
	int a=3, b=11;
	printf("%d & %d = %d\n",a ,b ,a&b);
	printf("%d | %d = %d\n",a ,b ,a|b);
	printf("%d ^ %d = %d\n",a ,b ,a^b);
	printf("~%d == %d\n",a ,~a);

	return 0;
}
