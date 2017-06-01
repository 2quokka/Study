#include <stdio.h>

int main(){

// 반복문 내에서 출력 후 break 를 하면서 동작을 확인
	while(1)
	{
		while(1)
		{
			while(1)
			{
				printf("3\n");
					break;
			}
			printf("2\n");
			break;
		}
		printf("1\n");
		break;
	}

	printf("main\n");

	return 0;
}
