#include <stdio.h>

int main(){

	int pen;   //펜가격
	int pen_n; //구입할 펜 개수
	int deposit; //입금한 금액
	int change; // 거스름돈

	printf("pen price : "); scanf("%d", &pen);
	printf("pen num : "); scanf("%d",&pen_n);
	printf("deposit : "); scanf("%d",&deposit);

	//change = deposit-(pen * pen_n);

	if((change= deposit - (pen * pen_n)) < 0)
	{
		printf("no enought\n");
		return 0;
	}
	
	printf("change : %d\n", change);
	
	return 0;
}
