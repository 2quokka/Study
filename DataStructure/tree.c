#include <stdio.h>

typedef struct BinTreeNode
{
    int data;
}BinTreeNode;

typedef struct ArrayBinTreeType
{
    int maxCount;
    int currentCount;
    BinTreeNode *pData;
} ArrayBinTree;

ArrayBinTree* makeArrayBT(int maxcount);
int makeNodeBT(ArrayBinTree* pTree, int data);
BinTreeNode* addLeftChildNodeBT(BinTreeNode* pParentNode, int data);
BinTreeNode* addRightChildNodeBT(BinTreeNode* pParentNode, int data);
BinTreeNode* getRootNodeBT(BinTree* pBinTree);
void deleteBinTreeNode(BinTreeNode* pNode);
void deleteBinTree(BinTree* pBinTree);

int main(void)
{

    return 0;
}
ArrayBinTree* makeArrayBT(int maxcount){
    
int makeNodeBT(ArrayBinTree* pTree, int data);
BinTreeNode* addLeftChildNodeBT(BinTreeNode* pParentNode, int data);
BinTreeNode* addRightChildNodeBT(BinTreeNode* pParentNode, int data);
BinTreeNode* getRootNodeBT(BinTree* pBinTree);
void deleteBinTreeNode(BinTreeNode* pNode);
void deleteBinTree(BinTree* pBinTree);
