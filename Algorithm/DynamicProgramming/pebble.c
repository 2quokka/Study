#include <stdio.h>

int matrix[3][8] = { 6, 7, 12, -5, 5, 3, 11, 3,
                     -8, 10, 14, 9, 7, 13, 8, 5,
                     11, 12, 7, 4, 8, -2, 9, 4};
int cal[4][8];

int max(int a, int b);
int pebbleSum(int n);

int main(void){

    printf("%d \n ", pebbleSum(8));
    return 0;
}

int pebbleSum(int n){
    int p, i;

    for( p = 0; p < 4; p++){
        cal[p][0] = matrix[p][0];

        if(p == 3){
            cal[p][0] = matrix[0][0] + matrix[2][0];
        }
    }

    for(i = 1; i < n ; i++ ){
        for(p = 0 ; p < 4 ; p++){
            switch(p){
                case 0:
                    cal[p][i] = max(matrix[1][i],matrix[2][i]);
                    break;
                case 1:
                    cal[p][i] = max(matrix[0][i] + matrix[2][i] , max(matrix[0][i], matrix[2][i]));
                    break;
                case 2:
                    cal[p][i] = max(matrix[0][i], matrix[1][i]);
                    break;
                case 3:
                    cal[p][i] = matrix[1][i];
            }
        }
    }

    return max(max(cal[0][n-1], cal[1][n-1]), max(cal[2][n-1], cal[3][n-1]));
}

int max(int a, int b){
    return a > b ? a : b;
}
