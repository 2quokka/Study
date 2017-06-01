#include <stdio.h>

int main(){

	int *p, q;
	q=3;
	p= &q;
	*p=*p*3;  //q= 9
	*p=*p*q;  //  q= 81

	printf(" q= %d \n", q);

	return 0;
}

