#include <stdio.h>

void selectsort(int dataSet[], int n);
int largestVal(int dataSet[], int last);

int main(void){
    int dataSet[] = {12, 70, 30, 20, 55, 25, 40, 50};
    int i;

    selectsort(dataSet, 8);

    for(i = 0 ; i < 8 ; i ++)
        printf("%d ", dataSet[i] );

    return 0;
}

void selectsort(int dataSet[], int n){
    int i;
    int largest, tmp;

    for ( i = n-1 ; i > 0 ; i --){
        largest = largestVal(dataSet, i);

        //swap
        tmp = dataSet[i];
        dataSet[i] = dataSet[largest];
        dataSet[largest] = tmp;
    }
}

int largestVal(int dataSet[], int last) { // index return
    int i;
    int largest = 1; //index

    for(i = 0; i < last ; i++)
    {
        if(dataSet[largest] < dataSet[i])
            largest = i;
    }

    return largest;
}
