#include <stdio.h>

int main(){

	int a, b, quotient, rest; // 분모 분자 몫 나머지

	printf("insert value a/b (a b) : "); scanf("%d %d", &a, &b);

	if(b==0){
		printf("Divide by 0\n"); 
		return 0;
	}

	quotient = a / b;
	rest = a % b;

	printf("quotient : %d rest : %d \n", quotient, rest);
	return 0;
}
