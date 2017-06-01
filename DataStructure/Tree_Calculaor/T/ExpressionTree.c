#include "ExpressionTree.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ETNode* ET_CreateNode(char Operator, double NewData)
{
	ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;
	NewNode->Operator = Operator;
	return NewNode;
}

void ET_DestroyNode(ETNode* Node)
{
	free(Node);
}

void ET_DestroyTree(ETNode* Root)
{
	if (Root == NULL)
		return;

	ET_DestroyTree(Root->Left);
	ET_DestroyTree(Root->Right);
	ET_DestroyNode(Root);
}

void ET_PreorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	if (Node->Operator == 0)
		printf(" %g", Node->Data);
	else
		printf(" %c", Node->Operator);

	ET_PreorderPrintTree(Node->Left);
	ET_PreorderPrintTree(Node->Right);
}

void ET_InorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf("(");
	ET_InorderPrintTree(Node->Left);

	if (Node->Operator == 0)
		printf(" %g", Node->Data);
	else
		printf(" %c", Node->Operator);

	ET_InorderPrintTree(Node->Right);
	printf(")");
}

void ET_PostorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	ET_PostorderPrintTree(Node->Left);
	ET_PostorderPrintTree(Node->Right);
	if (Node->Operator == 0)
		printf(" %g", Node->Data);
	else
		printf(" %c", Node->Operator);
}

void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
{
	ETNode* NewNode = NULL;
	char temp[100];
	int i, len = strlen(PostfixExpression);
	char Token = PostfixExpression[len - 1];
	PostfixExpression[len - 1] = '\0';

	if (len == 0)
		return;
	if (Token == ' ') {
		while (Token == ' ') {
			len = strlen(PostfixExpression);
			Token = PostfixExpression[len - 1];
			PostfixExpression[len - 1] = '\0';
		}
	}

	switch (Token)
	{
	
	case '+': case '-': case '*': case '/': case '%': case '^':
		(*Node) = ET_CreateNode(Token, 0);
		ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
		ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
		break;


	default:
		i = 0;
		while (Token != ' ')
		{
			if (Token == 'a')
			{
				temp[i++] = '-';
				temp[i++] = '1';
			}
			temp[i++] = Token;
			len = strlen(PostfixExpression);

			if (len == 0)
				break;
			Token = PostfixExpression[len - 1];
			PostfixExpression[len - 1] = '\0';
		}
		temp[i] = '\0';

		reverseString(temp);
		(*Node) = ET_CreateNode(0, atof(temp));
		break;
	}
}

double ET_Evaluate(ETNode* tree)
{
	double Left = 0;
	double Right = 0;
	double Result = 0;

	if (tree == NULL)
		return 0;

	switch (tree->Operator)
	{

	case '+': case '-': case '*': case '/': case '%': case '^':
		Left = ET_Evaluate(tree->Left);
		Right = ET_Evaluate(tree->Right);

		if (tree->Operator == '+') Result = Left + Right;
		else if (tree->Operator == '-') Result = Left - Right;
		else if (tree->Operator == '*') Result = Left * Right;
		else if (tree->Operator == '/') Result = Left / Right;
		else if (tree->Operator == '%') Result = fmod(Left, Right);
		else if (tree->Operator == '^') Result = pow(Left, Right);

		break;

	default:
		Result = tree->Data;
		break;
	}
	return Result;
}

void reverseString(char* s) {
	size_t size = strlen(s);
	char temp;

	for (size_t i = 0; i < size / 2; i++) {
		temp = s[i];
		s[i] = s[(size - 1) - i];
		s[(size - 1) - i] = temp;
	}
}
