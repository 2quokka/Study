#include <stdio.h>

void bubbleSort(int dataSet[], int n);

int main(void){
    int dataSet[] = { 10, 5, 32, 11, 25, 17};
    int i;

    bubbleSort(dataSet, 6);

    for(i=0; i<6; i++)
        printf("%d ", dataSet[i]);

    return 0;
}
void bubbleSort(int dataSet[], int n){
    int last;
    int i, tmp;

    for( last = n-1 ; last >= 1 ; last --){
        for( i = 1 ; i <= last ; i ++) {
            if( dataSet[i-1] > dataSet[i] ){
                tmp = dataSet[i];
                dataSet[i] = dataSet[i-1];
                dataSet[i-1] = tmp;
            }
        }
    }
}

            
        
        

