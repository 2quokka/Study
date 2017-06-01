#include <stdio.h>

int main(){

	double height;

	printf("height : ");
	scanf("%lf", &height);

	printf("%0.1f\n",(height-100) * 0.9);

return 0;
}
