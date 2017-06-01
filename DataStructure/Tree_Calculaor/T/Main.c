#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ExpressionTree.h"
#include "ExpressionStack.h"

#define TRUE 1
#define FALSE 0

typedef unsigned char BOOL;

extern char expr[MAX_EXPR_SIZE];

BOOL exprCheck(char *expr);

int main()
{
	ETNode* Root = NULL;
	char *del_expr, *in_expr, *post_expr;
	int i = 0;
	double result;

	while(1)
	{
		printf("insert Expression (exit : q || Q ):  ");
		fgets(expr, MAX_EXPR_SIZE, stdin);
		expr[strlen(expr)-1] = '\0';

		if (!strcmp(expr, "q") || !strcmp(expr, "Q"))
			break;

		if (!exprCheck(expr)) {
			printf("Invalid Expression ! \n");
			continue;
		}

		del_expr = deleteSpace(expr);//malloc

		printf("Space Delete Expression : %s\n", del_expr);
		in_expr = infix(del_expr); // malloc 
        free(del_expr);
		printf("Stack Inorder Expression : %s\n", in_expr);
		post_expr = postfix(in_expr); //malloc 
        free(in_expr);
		printf("Stack Postfix Expression: %s\n", post_expr);
		result = calc(post_expr);

		printf("= %lf \n\n", result);

		ET_BuildExpressionTree(post_expr, &Root);

        free(post_expr);

		printf("==================+TREE+==================\n\n");
		printf("---------Preorder----------\n");
		ET_PreorderPrintTree(Root);
		printf("\n\n");

		printf("---------Inorder-----------\n");
		ET_InorderPrintTree(Root);
		printf("\n\n");

		printf("---------Postorder---------\n");
		ET_PostorderPrintTree(Root);
		printf("\n\n");

		printf("Result : %f \n", ET_Evaluate(Root));

		printf("\n==========================================\n\n");
		ET_DestroyTree(Root);
	}

	return 0;
}


BOOL exprCheck(char *expr) {
	int i, len = strlen(expr);
	char *check = malloc(len + 1); 
	BOOL operatorCheck = FALSE, operandCheck = FALSE, parenCheck = FALSE;
	int lpCount = 0, rpCount = 0; 
	char token;

	strcpy(check, expr);

	for (i = 0; i < len; i++)
	{
		token = check[i];
		switch (token)
		{
		case ' ': case'.': 
			break;
		case '(':
			lpCount++;
			break;
		case ')':
			rpCount++;
			break;
		case '+': case '-': case '*': case '/': case '%': case '^':
			if(!operatorCheck)
				operatorCheck = TRUE;
			break;
		default:
			if (token >= '0' && token <= '9') {
				if(!operandCheck)
					operandCheck = TRUE;
				break;
			}
			else
				return FALSE;
		}
	}

	free(check);

	if (operandCheck && operatorCheck && (lpCount == rpCount))
		return TRUE;

	return FALSE;
}
