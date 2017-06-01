#include <stdio.h>

int main()
{
	char a;
	int num,i;

	while(1)
	{
		printf("insert alphabet ('q' is exit ): "); scanf("%c",&a);
		if(a=='q')  //q 입력시 반복문 빠져나감
			break;
		printf("insert number : "); scanf("%d", &num);
		for(i=0; i < num; i++)
			printf("%c \n", a);
	}
 return 0;
}
