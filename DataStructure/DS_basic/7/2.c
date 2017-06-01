#include <stdio.h>
#define PI 3.14

double circleArea(int r){return PI*r*r;}

int main(){

	int r;
	printf("circle radius : "); scanf("%d", &r);

	printf("area : %lf \n", circleArea(r));

	return 0;
}
