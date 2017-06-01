#include <stdio.h>

#define ROW 4
#define COL 4

int max(int a, int b);
int calPath(int m, int n);

int cal[ROW][COL];

int matrix[ROW][COL] = {6, 7, 12, 5,
                        5, 3, 11, 18,
                        7, 17, 3, 3,
                        8, 10, 14, 9};

int main(void) { 

    printf(" %d \n", calPath(ROW,COL));
    return 0;
}

int calPath(int m, int n){

    int i, j;

    cal[0][0] = matrix[0][0];

    for( i = 1 ; i < m ; i ++)
        cal[i][0] = matrix[i][0] + cal[i-1][0];

    for( j = 1 ; j < n ; j ++)
        cal[0][j] = matrix[0][j] + cal[0][j-1];
    
    for( i = 1 ; i < m ; i ++)
        for( j = 1 ; j < n ; j ++)
            cal[i][j] = matrix[i][j] + max( cal[i-1][j], cal[i][j-1] );

   return cal[m-1][n-1];
}

int max(int a, int b){
    return (a > b) ? a : b;
}
