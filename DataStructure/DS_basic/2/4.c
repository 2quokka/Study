#include <stdio.h>

int main(){

	int mon,day,hour,minute,second;

	printf("month : "); scanf("%d", &mon);

	day = mon * 30;
	hour = day * 24;
	minute = hour * 60;
	second = minute * 60;

	printf("hour : %d \n", hour);
	printf("minute : %d \n", minute);
	printf("second : %d \n", second);

	return 0;
}
