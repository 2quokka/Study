#include <stdio.h>

#define COL 8

void main()
{
	int matrix[4][COL]={
                   {6, 7, 12, -5, 5, 3, 11, 3 },
                   {-8, 10, 14, 9, 7, 13, 8, 5},
                   {11, 12, 7, 4, 8, -2, 9, 4}
                  };
    int peb[4][COL];
	int p, i, j, max, max_p;

	for( p = 0 ; p < 3 ; p ++ )
		peb[p][0] = matrix[p][0];

	for(i=0;i<COL;i++)
		matrix[3][i] = matrix[0][i] + matrix[2][i];

	peb[3][0]=matrix[3][0];

	for(i=1;i<COL;i++)
	{
		for(p=0;p<4;p++)
		{
			peb[p][i]=matrix[p][i];
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

    max_p = 0;

	for(p=0; p<4; p++)
	{
		if(peb[max_p][COL-1] < peb[p][COL-1])
			max_p = p;
	}

	printf("MAXIMUM VAL : %d\n\n",peb[max_p][COL-1]);
}
