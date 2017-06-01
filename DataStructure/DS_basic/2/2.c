#include <stdio.h>

int main(void){

	int mid_grade;
	int final_grade;
	double avg=0.0;

	printf("insert mid_grade :");
	scanf("%d", &mid_grade);

	printf("insert final_grade :");
	scanf("%d", &final_grade);

	//	avg = (mid_grade + final_grade) / 2;
	printf("average : %lf\n", (double)(mid_grade + final_grade) / 2);
	return 0;
}
