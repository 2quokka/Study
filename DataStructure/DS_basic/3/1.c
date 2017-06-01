#include <stdio.h>

int main(){

	int age, fee;  //나이 요금 변수

	printf("age : "); scanf("%d", &age);

	if(age <= 3)
		fee=0;
	else if(age <= 7)
		fee = 100;
	else if(age <= 12)
		fee = 250;
	else if(age <= 18)
		fee = 350;
	else
		fee = 500;
	
	printf("fee : %d \n", fee);

	return 0;
}
