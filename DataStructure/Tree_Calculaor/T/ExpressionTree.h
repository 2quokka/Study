//ExpressionTree.h

#ifndef EXPRESSION_TREE
#define EXPRESSION_TREE

typedef struct tagETNode
{
	struct tagETNode* Left;
	struct tagETNode* Right;

	char Operator;
	double Data;
} ETNode;

ETNode*   ET_CreateNode(char Operator, double NewData);
void      ET_DestroyNode(ETNode* Node);
void      ET_DestroyTree(ETNode* Root);

void      ET_PreorderPrintTree(ETNode* Node);
void      ET_InorderPrintTree(ETNode* Node);
void      ET_PostorderPrintTree(ETNode* Node);
void      ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node);
double	  ET_Evaluate(ETNode* tree);

void reverseString(char* s);
#endif