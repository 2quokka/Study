// WordTree.h

typedef struct TreeNode {
    char alphabet;
    char *meaning;
    struct TreeNode *brother;
    struct TreeNode *child;
} TreeNode;

TreeNode** makeTreeNode(TreeNode **ptr, char alphabet, char *meaning);
void removeTreeNode(TreeNode *ptr);

