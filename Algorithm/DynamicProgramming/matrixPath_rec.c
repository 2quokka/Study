#include <stdio.h>

#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )
#define ROW 4
#define COL 4

int matrixPath(int i, int j);

int matrix[ROW][COL] = {6, 7, 12, 5,
                        5, 3, 11, 18,
                        7, 17, 3, 3,
                        8, 10, 14, 9};
int main(void){

    printf("MAX PATH VAL : %d\n", matrixPath(ROW, COL));

    return 0;
}
int matrixPath(int i, int j){
    if(i == 0 && j == 0)
        return matrix[0][0];
    else if(i == 0)
        return matrix[i][j] + matrixPath(i, j-1);
    else if(j == 0)
        return matrix[i][j] + matrixPath(i-1, j);
    else
        return matrix[i][j] + MAX(matrixPath(i-1, j) , matrixPath(i,j-1));
}

