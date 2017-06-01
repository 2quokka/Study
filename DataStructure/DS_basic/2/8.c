#include <stdio.h>
#include <limits.h> //INT_MAX, LONG_MAX

int main(){

	printf("sizeof int : %d \n",sizeof(int));
	printf("sizeof long : %d \n",sizeof(long));
	printf("sizeof float : %d \n",sizeof(float));
	printf("sizeof double : %d \n",sizeof(double));
	puts("");


	printf("int max value : %d \n", INT_MAX);
	printf("long max value : %ld \n", LONG_MAX);  // 서식지정자 ld 
	
return 0;
}
