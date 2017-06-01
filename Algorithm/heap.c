#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATANUM 5
#define RANDMAX 100

void heapify(int dataSet[], int node, int nodeNum);
void buildHeap(int dataSet[], int nodeNum);
void heapSort(int dataSet[], int nodeNum);

void reverse(int A[], int n);

int main(void){

    int dataSet[DATANUM+1];
    int i;
    
    dataSet[0] = 0;

    srand( (unsigned int) time(NULL) );
    printf(" before sort \n");
    for(i=1;i<=DATANUM;i++){
        dataSet[i] = rand() % RANDMAX;
        printf("dataSet[%d] = %d \n", i, dataSet[i]);
    }

    heapSort(dataSet, DATANUM);
    
    printf(" after sort \n");
    for(i=1; i<=DATANUM; i++){
        printf("dataSet[%d] = %d \n", i, dataSet[i]);
    }
    
    return 0;
}
void heapify(int dataSet[], int node, int nodeNum){
    int left, right, smaller, tmp;

    left = 2 * node;
    right = 2 * node + 1;
    if(right <= nodeNum){
        if(dataSet[left] > dataSet[right])
            smaller = left;

        else
            smaller = right;
    }
    else if(left <= nodeNum)
        smaller = left;
    else
        return;

    if(dataSet[smaller] > dataSet[node]){
        tmp = dataSet[smaller];
        dataSet[smaller] = dataSet[node];
        dataSet[node] = tmp;

        heapify(dataSet, smaller, nodeNum);
    }
}

void buildHeap(int dataSet[], int nodeNum){
    int i;
    for(i = nodeNum/2 ; i >= 1 ; i--)
        heapify(dataSet, i, nodeNum);
}

void heapSort(int dataSet[], int nodeNum){
    int i, tmp;

    buildHeap(dataSet, nodeNum);
    
    for(i = nodeNum ; i >= 2 ; i--){
        tmp = dataSet[1];
        dataSet[1] = dataSet[i];
        dataSet[i] = tmp;

        heapify(dataSet, 1, i-1);
    }
}

void reverse(int A[], int n){
    int tmp, i;

    for(i = 1; i <= n/2 ; i++){
        tmp = A[i];
        A[i] = A[n+1-i];
        A[n+1-i] = tmp;
    }
}
