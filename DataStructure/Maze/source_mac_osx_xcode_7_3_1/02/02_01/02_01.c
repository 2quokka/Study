#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayListNodeType {
    int data;
} ArrayListNode;

typedef struct ArrayListType {
    int maxCount;           // 최대 자료 개수: 배열의 크기
    int currentCount;       // 현재 자료의 개수
    ArrayListNode *pData;   // 자료 저장을 위한 1차원 배열
} ArrayList;

ArrayList *createList(int count)
{
    ArrayList *pReturn = (ArrayList *)malloc(sizeof(ArrayList));
    pReturn->maxCount = count;
    pReturn->currentCount = 0;
    pReturn->pData = (ArrayListNode *)malloc(sizeof(ArrayListNode) * count);
    memset(pReturn->pData, 0, sizeof(ArrayListNode) * count);
    
    return pReturn;
}

int addListData(ArrayList* pList, int position, int data)
{
    int i = 0;
    for(i = pList->currentCount-1; i >= position; i--) {
        pList->pData[i+1] = pList->pData[i];
    }
    pList->pData[position].data = data;
    pList->currentCount++;
    
    return 0;
}

int removeListData(ArrayList* pList, int position)
{
    int i = 0;
    for(i = position; i < pList->currentCount-1; i++) {
        pList->pData[i] = pList->pData[i+1];
    }
    pList->currentCount--;
    return 0;
}

int getListData(ArrayList* pList, int position)
{
    return pList->pData[position].data;
}

void deleteList(ArrayList* pList)
{
    free(pList->pData);
    free(pList);
}

int main(int argc, char *argv[])
{
    ArrayList *pList = NULL;
    int value = 0;
    
    pList = createList(5);              // Step-1
    addListData(pList, 0, 10);          // Step-2
    addListData(pList, 1, 20);          // Step-3
    addListData(pList, 0, 30);          // Step-4
    
    value = getListData(pList, 1);      // Step-5
    printf("위치: %d, 값: %d\n", 1, value);
    
    removeListData(pList, 0);           // Step-6
    deleteList(pList);                  // Step-7
    
    return 0;
}

