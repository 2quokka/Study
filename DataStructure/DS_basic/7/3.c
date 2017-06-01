#include <stdio.h>

char grade(int score){
	if(score >= 90)
		return 'A';
	else if(score >= 80)
		return 'B';
	else if(score >= 70)
		return 'C';
	else if(score >=60)
		return 'D';	
	else
		return 'F';
}

int main(){
	
	int score;
	printf("score : "); scanf("%d",&score);
	printf("grade : %C \n", grade(score));
	
	return 0;
}
