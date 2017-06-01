#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedstack.h"

char* reverseString(char *pSource)
{
    char* pReturn = NULL;
    int i = 0, size = 0;
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;
    
    pStack = createLinkedStack();
    if (pStack != NULL) {
        while(pSource[size] != '\0') {
            pushLS(pStack, pSource[size]);
            size++;
        }
        
        pReturn = (char *)malloc(sizeof(char) * (size + 1));
        memset(pReturn, 0, sizeof(char) * (size + 1));
        
        while(i < size) {
            pNode = popLS(pStack);
            if (pNode != NULL) {
                pReturn[i] = pNode->data;
                free(pNode);
            }
            i++;
        }
        deleteLinkedStack(pStack);
    }
    
    return pReturn;
}

int main(int argc, const char * argv[]) {
    char szSource[] = "ABCD";
   	char *pszReverse = reverseString(szSource);
    if (pszReverse != NULL) {
        printf("[%s] => [%s]\n", szSource, pszReverse);
        
        free(pszReverse);
    }
       return 0;
}

char* reverseString_complete2(char *pSource)
{
    char* pReturn = NULL;
    int i = 0, size = 0;
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;
    
    if (pSource == NULL) {
        return NULL;
    }
    
    pStack = createLinkedStack();
    if (pStack != NULL) {
        while(pSource[size] != 0) {
            pushLS(pStack, pSource[size]);
            size++;
        }
        
        if (size > 0) {
            pReturn = (char *)malloc(sizeof(char) * (size + 1));
            if (pReturn == NULL) {
                printf("메모리 할당이 실패하였습니다,reverseString()\n");
                return NULL;
            }
        }
        
        while(i < size) {
            pNode = popLS(pStack);
            if (pNode != NULL) {
                pReturn[i] = pNode->data;
                free(pNode);
            }
            i++;
        }
        deleteLinkedStack(pStack);
    }
    else {
        printf("메모리 할당이 실패하였습니다,createLinkedStack()\n");
        return NULL;
    }
    
    return pReturn;
}

char* reverseString_complete(char *pSource)
{
    char* pReturn = NULL;
    int i = 0, size = 0;
    LinkedStack *pStack = NULL;
    LinkedStackNode *pNode = NULL;
    
    if (pSource == NULL || pSource[0] == 0) {
        return NULL;
    }
    
    size = (int)strlen(pSource);
    pReturn = (char *)malloc(sizeof(char) * (size + 1));
    if (pReturn == NULL) {
        printf("메모리 할당이 실패하였습니다,reverseString()\n");
        return NULL;
    }
    memset(pReturn, 0, sizeof(char) * (size + 1));
    
    pStack = createLinkedStack();
    if (pStack != NULL) {
        for(i = 0; i < size; i++) {
            pushLS(pStack, pSource[i]);
        }
        
        for(i = 0; i < size; i++) {
            pNode = popLS(pStack);
            if (pNode != NULL) {
                pReturn[i] = pNode->data;
                free(pNode);
            }
        }
        deleteLinkedStack(pStack);
    }
    else {
        if (pReturn == NULL) {
            free(pReturn);
            pReturn = NULL;
        }
    }
    
    return pReturn;
}
