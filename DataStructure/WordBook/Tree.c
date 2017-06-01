#include "Tree.h"
#include "alphabet.h"
#include <stdlib.h>

LinkedBinaryTree* createLBT(){
    LinkedBinaryTree *ptr= (LinkedBinaryTree *)malloc(sizeof(LinkedBinaryTree));
    initializeLBT(ptr);
    return ptr;
}

void initializeLBT(LinkedBinaryTree *ptr){ptr->root = NULL;}
void deleteLBT(LinkedBinaryTree *ptr){
    if(ptr->root != NULL)
        deleteLBTNode(root);

    free(ptr);
}

LinkedBinaryTreeNode* createLBTNode(alphabet *al){
    LinkedBinaryTreeNode *ptr = (LinkedBinaryTreeNode *)malloc (sizeof(LinkedBinaryTreeNode));
    initializeLBTNode(ptr);
    ptr->al = al;
    return ptr;
}

void deleteLBTNode(LinkedBinaryTreeNode *ptr){
    if(ptr == NULL)
        return;
    else if(ptr->child ==NULL && ptr->brother == NULL)
    {
        deleteAlphabet(ptr->al);
        free(ptr);
        return;
    }
    else
    {
        deleteLBTNode(ptr->child);
        deleteLBTNode(ptr->brother);
        free(ptr);
        return;
    }
void initializeLBTNode(LinkedBinaryTreeNode *ptr){ptr->al = NULL; ptr->child = ptr->brother = NULL;}

int createChildNode(LinkedBinaryTreeNode *ptr, alphabet *al){
    if(ptr->child != NULL)
    {
        printf("existed child node!");
        return -1;
    }
    ptr->child=createLBTNode(al);
    return 0;
}

int createBrotherNode(LinkedBinaryTreeNode *ptr, alphabet *al){
    if(ptr->brother != NULL)
    {
        printf("existed child node!");
        return -1;
    }
    ptr->brother=createLBTNode(al);
    return 0;
}
void connectOnTheChild(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *child){
    parent->child = child;
}
void connectOnTheBrother(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *brother){
    parent->brother = brother;
}
