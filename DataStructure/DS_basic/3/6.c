#include <stdio.h>

void ch_1();
void ch_2();
void ch_3();
void ch_4();

int main(){

	int ch;

	printf("insert choice number :"); scanf("%d", &ch );


	switch(ch)
	{
		case 1:
			ch_1();
			break;
		case 2:
			ch_2();
			break;
		case 3:
			ch_3();
			break;
		case 4:
			ch_4();
			break;

	}
	return 0;
}

void ch_1(){

	int age, fee;

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
}

void ch_2(){
	
	int x,y;
	int max;

	printf("insert number 2 : "); scanf("%d %d", &x, &y);

	max= x>y ? x: y;

	printf("max : %d\n", max);
}

void ch_3(){
	
	int kor, eng, math, avg;

	printf("kor : "); scanf("%d", &kor);
	printf("eng : "); scanf("%d", &eng);
	printf("math : "); scanf("%d", &math);

	avg = (kor + eng + math)/3;

	if(kor >= 60 && eng >= 60 && math >= 60 && avg >= 70)
			printf("pass !\n");
	else
		printf("sorry ! \n");
}

void ch_4(){

	int num;

	printf("number :");
	scanf("%d", &num);

	if(num %2 ==0)
		printf("even!\n");
	else
		printf("odd!\n");

}
