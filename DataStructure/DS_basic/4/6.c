#include <stdio.h>

int main()
{
	int i,j;
	char a;
	for(i=0; i<5;i++)
	{
		a=getchar();
		getchar();  //ENTER 처리
		for(j=0;j<a;j++)   //아스키 코드 만큼 출력
			printf("+");
		printf("\n");
	}

	return 0;
}
