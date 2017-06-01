#include <stdio.h>

int main(){

	int x,y;
	int max;

	printf("insert number 2 : "); scanf("%d %d", &x, &y);

	max= x>y ? x: y;  //3항 연산자 사용 

	printf("max : %d\n", max);

	return 0;
}
