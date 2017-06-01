#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType {
    int data;
    struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType {
    int             currentCount;
    LinkedListNode  *headerNode;
} LinkedList;


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

LinkedListNode* makeNode(int data)
{
    LinkedListNode *tmp = malloc(sizeof(LinkedListNode));
    tmp -> data = data;
    tmp -> pLink = NULL;

    return tmp;
}
void print(LinkedList *list)
{
    LinkedListNode * ptr = list->headerNode;

    while(ptr)
    {
        printf("%2d ",ptr->data);
        ptr=ptr->pLink;
    }
    printf("\n");
}


int main()
{
    LinkedListNode *tmp;
    LinkedList *list = malloc(sizeof(LinkedList));
    list -> currentCount =0;

    list -> headerNode = makeNode(4);
    list -> currentCount++;
    list -> headerNode -> pLink = makeNode(2);
    list -> currentCount++;
    list -> headerNode -> pLink -> pLink = makeNode(5);
    list -> currentCount++;

    print(list);

    sort(list);

    print(list);

    //free list ~
    return 0;
}
