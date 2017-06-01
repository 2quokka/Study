#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType {
    int data;
    struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType {
    int             currentCount;
    LinkedListNode  headerNode;
} LinkedList;

LinkedList *createLinkedList() {
    LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
    memset(pReturn, 0, sizeof(LinkedList));
    return pReturn;
}

int getLinkedListData(LinkedList* pList, int position) {
    int i = 0;
    
    LinkedListNode *pCurrentNode = &(pList->headerNode);
    for (i = 0; i <= position; i++) {
        pCurrentNode = pCurrentNode->pLink;
    }
    
    return pCurrentNode->data;
}

int addLinkedListData(LinkedList* pList, int position, int data) {
    int i = 0;
    LinkedListNode *pNewNode = NULL;
    LinkedListNode *pPreNode = NULL;
    
    pNewNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    pNewNode->data = data;
    
    pPreNode = &(pList->headerNode);
    for (i = 0; i < position; i++) {
        pPreNode = pPreNode->pLink;
    }
    
    pNewNode->pLink = pPreNode->pLink;
    pPreNode->pLink = pNewNode;
    pList->currentCount++;
    return 0;
}

int removeLinkedListData(LinkedList* pList, int position) {
    int i = 0;
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = NULL;
    
    pPreNode = &(pList->headerNode);
    for (i = 0; i < position; i++) {
        pPreNode = pPreNode->pLink;
    }
    
    pDelNode = pPreNode->pLink;
    pPreNode->pLink = pDelNode->pLink;
    free(pDelNode);
    pList->currentCount--;
    return 0;
}

void deleteLinkedList(LinkedList* pList) {
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = pList->headerNode.pLink;
    while(pPreNode != NULL) {
        pDelNode = pPreNode;
        pPreNode = pPreNode->pLink;
        
        free(pDelNode);
    }
    
    free(pList);
}

int getLinkedListLength(LinkedList* pList) {
    if (NULL != pList) {
        return pList->currentCount;
    }
    return 0;
}

void sort(LinkedList* pList){
    int i;
    LinkedListNode *previous = NULL;
    LinkedListNode *current = NULL;
    LinkedListNode *next = NULL;

    if(pList != NULL )
    {
        for(i = 0 ; i < pList->currentCount -1 ; i++)
        {
            current = pList->headerNode;
            next = current -> pLink;

            while(next != NULL)
            {
                if(current -> data > next -> data)
                {
                    current -> pLink = next -> pLink;
                    next -> pLink = current;

                    if(previous == NULL) //current is head
                    {
                        pList -> headerNode = next;
                    }
                    else
                    {
                        previous -> pLink = next;
                    }

                    previous = next;
                    next = current -> pLink;
                }
                else
                {
                    previous = current;
                    current = next;
                    next = next -> pLink;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    LinkedList *pList = NULL;
    int value = 0;
    
    pList = createLinkedList();
    addLinkedListData(pList, 0, 10);
    addLinkedListData(pList, 1, 20);
    addLinkedListData(pList, 1, 30);
    
    value = getLinkedListData(pList, 1);
    printf("위치: %d, 값: %d\n", 1, value);
    
    removeLinkedListData(pList, 1);
    deleteLinkedList(pList);
    
    return 0;
}

