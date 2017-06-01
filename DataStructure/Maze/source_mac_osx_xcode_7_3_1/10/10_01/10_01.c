#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HeapNodeType
{
    int data;
} HeapNode;

typedef struct ArrayHeapType
{
    int maxCount;           // 최대 노드 개수
    int currentCount;       // 현재 노드 개수
    HeapNode *pData;		// 노드 저장을 위한 1차원 array
} ArrayMaxHeap, ArrayMinHeap;

ArrayMaxHeap* createArrayMaxHeap(int maxCount)
{
    ArrayMaxHeap *pReturn = NULL;
    if (maxCount > 0) {
        pReturn = (ArrayMaxHeap *)malloc(sizeof(ArrayMaxHeap));
        pReturn->maxCount = maxCount;
        pReturn->currentCount = 0;
        pReturn->pData = (HeapNode *)malloc(sizeof(HeapNode) * (maxCount + 1));
        memset(pReturn->pData, 0, sizeof(HeapNode) * (maxCount+1));
    }
    else {
        printf("최대 원소 개수는 0보다 커야 합니다\n");
    }
    
    return pReturn;
}

int insertMaxHeapAH(ArrayMaxHeap* pHeap, int value)
{
    int i = 0;
    
    if (pHeap != NULL) {
        if (pHeap->currentCount ==  pHeap->maxCount) {
            printf("오류, 히프가 가득찼습니다[%d],insertMaxHeapAH()\n",
                   pHeap->maxCount);
            return 0;
        }
        
        pHeap->currentCount++;
        i =  pHeap->currentCount;
        while((i != 1) && (value > pHeap->pData[i/2].data)) {
            pHeap->pData[i] = pHeap->pData[i/2];
            i /= 2;
        }
        pHeap->pData[i].data = value;
    }
    
    return i;
}

HeapNode* deleteMaxHeapAH(ArrayMaxHeap* pHeap)
{
    HeapNode* pReturn = NULL;
    HeapNode* pTemp = NULL;
    int parent =1, child = 2;
    
    if (pHeap != NULL && pHeap->currentCount >  0) {
        pReturn = (HeapNode*)malloc(sizeof(HeapNode));
        if (pReturn == NULL) {
            printf("오류, 메모리 할당, deleteMaxHeapAH()\n");
            return NULL;
        }
        pReturn->data = pHeap->pData[ 1 ].data;
        
        pTemp = &(pHeap->pData[ pHeap->currentCount ]);
        pHeap->currentCount--;
        
        while(child <= pHeap->currentCount) {
            if ((child < pHeap->currentCount)
                && pHeap->pData[ child ].data < pHeap->pData[ child+1 ].data) {
                child++;
            }
            if (pTemp->data >= pHeap->pData[ child ].data) {
                break;
            }
            
            pHeap->pData[ parent ] = pHeap->pData[ child ];
            parent = child;
            child *= 2;
        }// end-of-while
        pHeap->pData[ parent ] = *pTemp;
    }
    
    return pReturn;
}

void deleteArrayMaxHeap(ArrayMaxHeap* pHeap)
{
    if (pHeap != NULL) {
        if (pHeap->pData != NULL) {
            free(pHeap->pData);
        }
        free(pHeap);
    }
}


void displayArrayHeap(ArrayMaxHeap* pHeap)
{
    int i = 0;
    if (pHeap != NULL) {
        for(i = 1; i <= pHeap->currentCount; i++) {
            printf("[%d],%d\n", i, pHeap->pData[i].data);
        }
    }
}

int main(int argc, char *argv[])
{
    int maxHeapSize = 20;
    ArrayMaxHeap *pHeap1 = NULL;
    HeapNode *pNode = NULL;
    
    pHeap1 = createArrayMaxHeap(maxHeapSize);
    if (pHeap1 != NULL) {
        insertMaxHeapAH(pHeap1, 90);
        insertMaxHeapAH(pHeap1, 85);
        insertMaxHeapAH(pHeap1, 80);
        insertMaxHeapAH(pHeap1, 75);
        insertMaxHeapAH(pHeap1, 70);
        insertMaxHeapAH(pHeap1, 65);
        insertMaxHeapAH(pHeap1, 60);
        insertMaxHeapAH(pHeap1, 55);
        insertMaxHeapAH(pHeap1, 50);
        insertMaxHeapAH(pHeap1, 45);
        insertMaxHeapAH(pHeap1, 40);
        insertMaxHeapAH(pHeap1, 35);
        insertMaxHeapAH(pHeap1, 30);
        
        printf("Max Heap:\n");
        displayArrayHeap(pHeap1);

        insertMaxHeapAH(pHeap1, 99);
        printf("After insertMaxHeapAH()-%d\nMax Heap:\n", 99);
        displayArrayHeap(pHeap1);

        pNode = deleteMaxHeapAH(pHeap1);
        if (pNode != NULL) {
            printf("deleteMaxHeapAH()-[%d]\n", pNode->data);
            free(pNode);
        }
        
        printf("Max Heap:\n");
        displayArrayHeap(pHeap1);
        
        deleteArrayMaxHeap(pHeap1);
    }
    
    return 0;
}


/*
ArrayMaxHeap* createArrayMaxHeap(int maxCount)
{
    ArrayMaxHeap *pReturn = NULL;
    int i = 0;
    
    if (maxCount > 0) {
        pReturn = (ArrayMaxHeap *)malloc(sizeof(ArrayMaxHeap));
        if (pReturn != NULL) {
            pReturn->maxCount = maxCount;
            pReturn->currentCount = 0;
            pReturn->pElement = (HeapNode *)malloc(sizeof(HeapNode) * (maxCount + 1));
            if (pReturn->pElement == NULL) {
                printf("오류, 2번째 메모리 할당, createArrayList()\n");
                free(pReturn);
                return NULL;
            }
            
            memset(pReturn->pElement, 0, sizeof(HeapNode) * (maxCount+1));
        }
        else {
            printf("오류, 메모리 할당, createArrayList()\n");
        }
    }
    else {
        printf("최대 원소 개수는 0보다 커야 합니다\n");
    }
    
    return pReturn;
}
 
*/
