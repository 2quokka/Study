#include <stdio.h>

int total_second(int hour, int minute, int second)
{
	return (hour*3600) + (minute*60) + second;
}

int main(){

	int hour, minute, second;

	printf("insert hour, minute, second :");
	scanf("%d %d %d",&hour, &minute, &second);
	
	printf("total _ second : %d \n", total_second(hour, minute, second));


	return 0;
}
