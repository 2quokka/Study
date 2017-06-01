#include <stdio.h>

int sum(int x, int y){return x+y;}

int main(){
	int x, y;
	printf("insert : "); scanf("%d %d", &x, &y);
	printf("sum : %d \n", sum(x,y));
	return 0;
}
