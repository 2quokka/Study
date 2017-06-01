#include <stdio.h>

int main(){

	int bal=0; //잔액
	int m,y=0; // 달 연도
	double rate;//연이율

	printf("rate of interest : "); scanf("%lf", &rate);

	while(y<30)
	{
		for(m=0; m < 12 ; m++)
		{
			bal += 100;
			printf("%d year ", y+1);
			printf("%d month \nbalance : %d \n", m+1, bal);
		}
		bal = bal + (bal * rate); //연이율 적용
		y++;
	}

	return 0;
}
