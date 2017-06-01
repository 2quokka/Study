#include "Tree.h"
#include <stdlib.h>

LinkedBinaryTree* createLBT(double num){
    LinkedBinaryTree *ptr= (LinkedBinaryTree *)malloc(sizeof(LinkedBinaryTree));
    initializeLTB(ptr);
    return ptr;
}

void initializeLTB(LinkedBinaryTree *ptr){ptr->root = NULL;}
void deleteLTB(LinkedBinaryTree *ptr){
    if(ptr->root != NULL)
        deleteLTBNode(root);

    free(ptr);
}

LinkedBinaryTreeNode* createLBTNode(double num){
    LinkedBinaryTreeNode *ptr = (LinkedBinaryTreeNode *)malloc (sizeof(LinkedBinaryTreeNode));
    initializeLTBNode(ptr);
    ptr->num = num;
    return ptr;
}

void deleteLBTNode(LinkedBinaryTreeNode *ptr){
    if(ptr == NULL)
        return;
    else if(ptr->left ==NULL && ptr->right == NULL)
    {
        free(ptr);
        return;
    }
    else
    {
        deleteLTBNode(ptr->left);
        deleteLTBNode(ptr->right);
        free(ptr);
        return;
    }
void initializeLBTNode(LinkedBinaryTreeNode *ptr){ptr->left = ptr->right = NULL;}

int createLeftNode(LinkedBinaryTreeNode *ptr, double num){
    if(ptr->left != NULL)
    {
        printf("existed child node!");
        return -1;
    }
    ptr->left=createLBTNode(num);
    return 0;
}

int createRightNode(LinkedBinaryTreeNode *ptr, double num){
    if(ptr->right != NULL)
    {
        printf("existed child node!");
        return -1;
    }
    ptr->right=createLBTNode(num);
    return 0;
}
void connectOnTheLeft(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *child){
    parent->left = child;
}
void connectOnTheRight(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *child){
    parent->right = child;
}
