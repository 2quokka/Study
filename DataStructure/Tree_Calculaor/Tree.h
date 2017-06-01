//Tree.h
#ifdef TREE_H
#define TREE_H

typedef struct LinkedBinaryTreeNode{
    double num;
    struct LinkedBinaryTreeNode *left;
    struct LinkedBinaryTreeNode *right;
}LinkedBinaryTreeNode;

typedef struct LinkedBinaryTree{
    LinkedBinaryTreeNode *root;
} LinkedBinaryTree;

LinkedBinaryTree* createLBT(double num); // tree create
void initializeLTB(LinkedBinaryTree *ptr);
void deleteLTB(LinkedBinaryTree *ptr);

//funtion 
LinkedBinaryTreeNode* createLBTNode(double num); //return created Node Pointer
void initializeLTBNode(LinkedBinaryTreeNode *ptr);

int createLeftNode(LinkedBinaryTreeNode *ptr, double num);
int createRightNode(LinkedBinaryTreeNode *ptr, double num);
void deleteLTBNode(LinkedBinaryTreeNode *ptr);
void connectOnTheLeft(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *child);
void connectOnTheRight(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *child);

#endif
