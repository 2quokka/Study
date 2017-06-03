#include <stdio.h>

#define COL 8

void main()
{
	int w[4][COL]={
                   {6, 7, 12, -5, 5, 3, 11, 3 },
                   {-8, 10, 14, 9, 7, 13, 8, 5},
                   {11, 12, 7, 4, 8, -2, 9, 4}
                  };

	int p, i, j, max; 
    int peb[4][COL];

	for( p = 0 ; p < 3 ; p ++ )
		peb[p][0] = w[p][0];

	peb[3][0]=w[0][0]+w[2][0];

	for(i=0;i<COL;i++)
		w[3][i]=w[0][i]+w[2][i];

	for(i=1;i<COL;i++)
	{
		for(p=0;p<4;p++)
		{
			peb[p][i]=w[p][i];
			switch(p)
			{
				case 0:
					if( peb[1][i-1] > peb[2][i-1] )
						max = peb[1][i-1];
					else
						max = peb[2][i-1];
					break;

				case 1:
					if( peb[0][i-1] > peb[2][i-1])
					{
						if( peb[0][i-1] > peb[3][i-1])
							max = peb[0][i-1];
						else
							max = peb[3][i-1];
					}
					else
					{
						if( peb[2][i-1] > peb[3][i-1])
							max = peb[2][i-1];
						else
							max = peb[3][i-1];
					}
					break;

				case 2:
					if( peb[0][i-1] > peb[1][i-1] )
						max = peb[0][i-1];
					else
						max = peb[1][i-1];
					break;

				case 3:
					max = peb[1][i-1];
					break;
			}
			peb[p][i] += max;
		}
	}


	max=peb[0][COL-1];
	for(p=0; p<4; p++)
	{
		if(max<peb[p][COL-1])
			max=peb[p][COL-1];
	}

	for(p=0; p<4; p++)
	{
		for(i=0; i<COL; i++)
			printf("%4d ",peb[p][i]);
		printf("\n");
	}

	printf("max %d\n",max);
}
