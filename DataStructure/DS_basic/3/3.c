#include <stdio.h>

int main(void){

	int kor, eng, math, avg;

	printf("kor : "); scanf("%d", &kor);
	printf("eng : "); scanf("%d", &eng);
	printf("math : "); scanf("%d", &math);

	avg = (kor + eng + math)/3;

	if(kor >= 60 && eng >= 60 && math >= 60 && avg >= 70)
			printf("pass !\n");
	else
		printf("sorry ! \n");


	return 0;
}
