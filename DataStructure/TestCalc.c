#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define TRUE 1
#define FALSE 0


//Definition Of Global variables
char OperatorStack[100];
char OperandStack[100];

int OperatorTop;
int OperandTop;

//Definition Of Global Function
void InitializeStack();
void OperatorPush(char);
void OperandPush(int);
char OperatorPop();
int OperandPop();

int IsEmptyOperatorStack();
int IsEmptyOperandStack();

int GreaterOpr(char, char);
int Calculate(int, int, char);

void main()
{
	char buf[80];
	int len, i, minus_flag = 0, nCount;
	char number[10];
	int opn1, opn2;
	char opr, c;
	char tmpopr;

	InitializeStack();

	printf("insert : ");
	fgets(buf, 80, stdin);
	buf[strlen(buf)-1] = '\0';

	len = strlen(buf);

	for (i = 0; i < len;i++) 
	{
		c = buf[i];

		if (c >= '0' && c <= '9')
		{
			memset(number, 0, 10);
			nCount = 0;
			while (1)
			{
				number[nCount++] = c;
				c = buf[++i];
				if (!(c >= '0' && c <= '9'))
					break;
			}
			number[nCount] = '\0';

			if (minus_flag != 1) OperandPush(atoi(number));   // '0' = 48
			else {
				minus_flag = 0;
				OperandPush(-(atoi(number)));
			}
		}

		if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (c == '-') {
				minus_flag = 1;
				c = '+';
			}

			if (IsEmptyOperatorStack())
				OperatorPush(c);
			else {
				opr = OperatorPop();
				if (GreaterOpr(opr, c)) {   
					opn2 = OperandPop();
					opn1 = OperandPop();

					opn1 = Calculate(opn1, opn2, opr);
					OperandPush(opn1);
					OperatorPush(c);
				}
				else {
					OperatorPush(opr);
					OperatorPush(c);
				}
			}
		}

		else if (c == '(') {
			OperatorPush(c);
		}
		else if (c == ')') {
			do {
				tmpopr = OperatorPop();
				if (tmpopr != '(') { // (
					opn2 = OperandPop();
					opn1 = OperandPop();

					opn1 = Calculate(opn1, opn2, tmpopr);
					OperandPush(opn1);
				}
			} while (tmpopr != '(');
		}
	}

	while (!IsEmptyOperatorStack()) {
		opn1 = OperandPop();
		opn2 = OperandPop();
		opr = OperatorPop();
		opn1 = Calculate(opn1, opn2, opr);
		OperandPush(opn1);
	}

	printf("%s = %d\n", buf, OperandPop());

} 

void InitializeStack()
{
	OperatorTop = 0;
	OperandTop = 0;
}

void OperatorPush(char opr)
{
	OperatorStack[OperatorTop++] = opr;
}

void OperandPush(int opn)
{
	OperandStack[OperandTop++] = opn;
}

char OperatorPop()
{
	return OperatorStack[--OperatorTop];
}

int OperandPop()
{
	return OperandStack[--OperandTop];
}

int IsEmptyOperandStack()
{
	if (OperandTop == 0)
		return TRUE;
	else return FALSE;
}

int IsEmptyOperatorStack()
{
	if (OperatorTop == 0)
		return TRUE;
	else return FALSE;
}


int GreaterOpr(char opr1, char opr2)
{
	if (opr1 == '*' || opr1 == '/') {
		if (opr2 == '+' || opr2 == '-')
			return TRUE;
		else return FALSE;
	}
	else return FALSE;
}

int Calculate(int opn1, int opn2, char opr)
{
	switch (opr) {
	case'+':
		opn1 = opn1 + opn2;
		break;
	case'*':
		opn1 = opn1 * opn2;
		break;
	case'/':
		opn1 = opn2 / opn1;
		break;
	}

	return opn1;
}
