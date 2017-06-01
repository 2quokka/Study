#include <stdio.h>
#define PI 3.14  //PI 정의


int main(){
	double area;
	double radius;

	printf("circle radius ? ");
	scanf("%lf", &radius);

	area= PI * radius * radius;

	printf("circle area : %0.2f \n", area);

	return 0;
}
