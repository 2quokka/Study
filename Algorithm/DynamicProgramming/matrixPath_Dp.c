#include <stdio.h>

#define DEBUG
#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )
#define ROW 4
#define COL 4

int matrixPath();
void pathPrint();

int matrix[ROW][COL] = {6, 7, 12, 5,
                        5, 3, 11, 18,
                        7, 17, 3, 3,
                        8, 10, 14, 9};
int cal[ROW][COL];

int main(void){

    printf("MAX PATH VAL : %d\n", matrixPath(ROW, COL));

    return 0;
}

int matrixPath(){
    int i, j;

    cal[0][0] = matrix[0][0];

    for( i = 1 ; i < ROW ; i ++ ){
        cal[i][0] = matrix[i][0] + cal[i-1][0];
    }

    for (j = 1 ; j < COL ; j ++ ){
        cal[0][j] = matrix[0][j] + cal[0][j-1];
    }

    for( i = 1 ; i < ROW ; i ++){
        for( j = 1 ; j < COL ; j ++)
            cal[i][j] = matrix[i][j] + MAX(cal[i-1][j], cal[i][j-1]);
    }

    pathPrint();

    return cal[ROW-1][COL-1];
    
}
void pathPrint(){
    int map[ROW][COL] = {0};
    int i, j;

    map[ROW-1][COL-1] = 1;
    map[0][0] = 1;

    i = ROW-1;
    j = COL-1;

    while( i || j ){

        if(i == 0)
            map[i][--j] = 1;
        else if(j == 0)
            map[--i][j] = 1;
        else{
            if(cal[i-1][j] > cal[i][j-1])
                map[--i][j] = 1;
            else
                map[i][--j] = 1;
        }
    }

    for(i = 0; i < ROW ; i++)
        for(j = 0 ; j < COL ; j ++)
            if(map[i][j])
                printf("(%d,%d)\n", i, j);

}

