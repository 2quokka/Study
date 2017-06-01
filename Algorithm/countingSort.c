#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define RANDMAX 100
#define DATANUM 5

void countingSort(int dataSet[], int n);

int main(void){

    int dataSet[DATANUM];
    int i;
    
    srand( (unsigned int) time(NULL) );
    printf(" before sort \n");
    for( i = 0 ; i < DATANUM ; i++){
        dataSet[i] = (rand() % RANDMAX) + 1;
        printf("dataSet[%d] = %d \n", i, dataSet[i]);
    }

    countingSort(dataSet, DATANUM);

    printf(" after sort \n");
    for( i = 0 ; i < DATANUM ; i++ ){
        printf("dataSet[%d] = %d \n", i, dataSet[i]);
    }
    
    return 0;
}

void countingSort(int dataSet[], int n){
    int i, j;
    int result[DATANUM+1], count[RANDMAX + 1];

    for( i =0 ; i <= RANDMAX ; i++ )
        count[i] = 0;

    for( j = 0 ; j < n ; j++ )
        count[ dataSet[j] ]++;

    for( i = 1 ; i <= RANDMAX ; i++)
        count[i] = count[i] + count[i-1];

    for( j = n-1 ; j >= 0 ; j-- ){
        result[ count[dataSet[j]] ] = dataSet[j];
        count[ dataSet[j] ]--;
    }

    for( i = 1 ; i <= n ; i ++)
        dataSet[i-1] = result[i];
}
