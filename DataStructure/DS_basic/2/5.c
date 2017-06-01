#include <stdio.h>

int main(){

	int fees; //학점당 수업료
	int credit; //학점
	
	int total_fees; // 총 수업료

	printf("fees: ");
	scanf("%d",&fees);
	printf("credit : ");
	scanf("%d",&credit);
	
	total_fees = fees * credit;  //총수업료 계산

	printf("total fees : %d \n", total_fees);
	return 0;
}
