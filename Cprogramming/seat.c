#include <stdio.h>
#define ROW 2
#define COL 10


int main(void)
{
	char ans1;
	int i, j, c, r, ans2;
	int seats[ROW][COL]={0}; //모든배열 값0 초기화

	while(1)
	{
		printf("좌석을 예약하시겠습니까? (y/n) ");
		scanf("%c", &ans1);
		getchar();

		if(ans1 == 'y')
		{
			printf("----------------------------------\n");
			printf(" 1  2  3  4  5  6  7  8  9  10 \n");
			printf(" 11 12 13 14 15 16 17 18 19 20 \n");
			printf("----------------------------------\n");

			for(i=0;i<ROW;i++)
			{
				for(j=0;j<COL;j++)
				{
					printf(" %d", seats[i][j]);
				}
				printf("\n");
			}

			printf("몇번째 좌석을 예약하시겠습니까? \n");
			scanf("%d",&ans2);
			getchar();

			if(ans2 <= 0 || ans2 > 20)
			{
				printf("1 - 20까지 입력해주세요 \n");
				continue;
			}

			r= (ans2-1) / COL;
			c= (ans2-1) % COL;

			if(seats[r][c] == 0)
			{
				seats[r][c] = 1;
				printf("예 약 완 료 \n");
			}
			else
				printf("이미 예약된 자리입니다. \n");
		}
		else
			break;
	}
	return 0;
}
