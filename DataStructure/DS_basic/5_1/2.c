#include <stdio.h>
#define SIZE  5

int main(){
	
	int stu_num[SIZE], stu_kor[SIZE], stu_eng[SIZE], stu_avg[SIZE];
	int i, max_num, min_num, max, min ;


	// 성적 입력
	for(i =0; i<SIZE;i++)
	{
		printf("------------%d-------------\n",i+1);
		printf("student num : "); scanf("%d", &stu_num[i]);
		printf("student kor score : "); scanf("%d", &stu_kor[i]);
		printf("student eng score : "); scanf("%d", &stu_eng[i]);
	}

	// 평균 연산뒤 번호와 평균을 출력
	for(i=0; i< SIZE; i++)
	{
		stu_avg[i] = (stu_kor[i] + stu_eng[i])/2;
		printf("student number : %d\n", stu_num[i]);
		printf("student average : %d \n", stu_avg[i]);
	}
	
	//초기값으로 초기화 
	max = stu_avg[0];
	min = stu_avg[0];
	
	max_num = stu_num[0];
	min_num = stu_num[0];

	for(i=0; i < SIZE ; i++)
	{
		if(max < stu_avg[i]) 
		{
			max=stu_avg[i];
			max_num = stu_num[i];
		}
		if(min > stu_avg [i]) 
		{
			min = stu_avg[i];
			min_num = stu_num[i];
		}
	}

	printf("max_avg : %d number : %d \n", max, max_num);
	printf("min_avg : %d number : %d \n", min, min_num);


	return 0;
}
