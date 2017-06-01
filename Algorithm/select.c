#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 10

int partition(int dataSet[], int p, int r);
int sel(int dataSet[], int p, int r, int i);

int main(void){
    int dataSet[MAX];
    int i;

    srand(time(NULL));

    for(i = 0 ; i < MAX ; i ++){
        dataSet[i] = rand() % 100 +1;
        printf("%d ", dataSet[i]);
        if( (i+1) % 5 == 0)
            printf("\n");
    }

    printf("sel 5 min value : %d \n ", sel(dataSet, 0, MAX-1, 5));

    return 0;
}
int partition(int dataSet[], int p, int r){
    int j, x = dataSet[r];
    int i = p-1;
    int tmp;

    for( j = p ; j < r ; j ++){
        if (dataSet[j] <= x){
            //swap
            tmp = dataSet[++i];
            dataSet[i] = dataSet[j];
            dataSet[j] = tmp;
        }
    }

    tmp = dataSet[i+1];
    dataSet[i+1] = dataSet[r];
    dataSet[r] = tmp;

    return i+1;
}

int sel(int dataSet[], int p, int r, int i){
    
    int q, k;   // q, pivot index

    if ( p == r )
        return dataSet[p];

    q = partition(dataSet, p, r);
    k = q - p + 1;

    if ( i < k )
        return sel(dataSet, p, q-1, i);
    else if(i == k)
        return dataSet[q];
    else
        return sel(dataSet, q+1,r, i-k);
}
   
