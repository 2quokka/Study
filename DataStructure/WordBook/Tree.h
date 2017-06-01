//Tree.h
#ifdef TREE_H
#define TREE_H

typedef struct LinkedBinaryTreeNode{
    alphabet *al;
    struct LinkedBinaryTreeNode *child;
    struct LinkedBinaryTreeNode *brother;
}LinkedBinaryTreeNode;

typedef struct LinkedBinaryTree{
    LinkedBinaryTreeNode *root;
} LinkedBinaryTree;

LinkedBinaryTree* createLBT(); // tree create
void initializeLBT(LinkedBinaryTree *ptr);
void deleteLBT(LinkedBinaryTree *ptr);

//funtion 
LinkedBinaryTreeNode* createLBTNode(alphabet *al); //return created Node Pointer
void initializeLBTNode(LinkedBinaryTreeNode *ptr);

int createChildNode(LinkedBinaryTreeNode *ptr, alphabet *al);
int createBrotherNode(LinkedBinaryTreeNode *ptr, alphabet *al);
void deleteLBTNode(LinkedBinaryTreeNode *ptr);
void connectOnTheChild(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *child);
void connectOnTheBrother(LinkedBinaryTreeNode *parent, LinkedBinaryTreeNode *brother);

#endif
