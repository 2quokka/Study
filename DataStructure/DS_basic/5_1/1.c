#include <stdio.h>
#define SIZE 10

int main(void)
{
    int i;
    int grade[SIZE];
    int sum = 0;

    for(i=0;i<SIZE;i++)
    {
    	fputs("insert grade : ",stdout);
		scanf("%d",&grade[i]);
    	sum += grade[i];
    }
    printf("average : %g \n",(double)sum/SIZE);
    return 0;
}
