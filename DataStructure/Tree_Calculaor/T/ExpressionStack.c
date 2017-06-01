#include "ExpressionStack.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

static int isp[] = { 0,19,12,12,13,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,13,0 };

char expr[MAX_EXPR_SIZE];

int top1 = 0;       
int top2 = -1;     

precedence stack1[MAX_STACK_SIZE];
double stack2[MAX_STACK_SIZE];   

char* deleteSpace(char *expr)
{
	char *delete_expr = (char *)malloc(strlen(expr) + 1);
	int i = 0, j = 0;
	while (expr[i])
	{
		if (expr[i] != ' ')
			delete_expr[j++] = expr[i++];
		else
			i++;
	}
	delete_expr[j] = '\0';

	return delete_expr;
}


char* infix(char *expr)
{
	int minusCnt = 0;
	int i = 0, j = 0;
	char *infix_expr = (char *)malloc(strlen(expr) + 1);

	while (expr[i])
	{
		if (expr[i] == '-' && i == 0)
		{
			
			while (expr[i] == '-')
			{
				minusCnt++;
				i++;
			}
			if (minusCnt % 2 == 0) { ; }
			else
			{
				infix_expr[j++] = 'a'; // a= > -1
				infix_expr[j++] = '*';
			}
			minusCnt = 0;

		}

		else if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '%' || expr[i] == '^' || expr[i] == ')' || expr[i] == '(')
		{
			infix_expr[j++] = expr[i++];
			if (expr[i] == '-')
			{
				
				while (expr[i] == '-')
				{
					minusCnt++;
					i++;
				}
				if (minusCnt % 2 == 0) { ; }
				else
				{
					infix_expr[j++] = 'a';
					infix_expr[j++] = '*';
				}
				minusCnt = 0;
			}
		}
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			infix_expr[j++] = expr[i];
			if (expr[++i] == '-')
			{
			
				while (expr[i] == '-')
				{
					minusCnt++;
					i++;
				}
				if (minusCnt % 2 == 0)
					infix_expr[j++] = '+';
				else
				{
					infix_expr[j++] = '-';
					minusCnt = 0;
				}
			}
			else if (expr[i] == '(')  
				infix_expr[j++] = '*';
		}
		else
			infix_expr[j++] = expr[i++];
	}
	infix_expr[j] = '\0';
	return infix_expr;
}

char * postfix(char *expr)
{
	char *postfix_expr = (char *)malloc(strlen(expr) + 1);
	int i = 0;
	precedence token;
	stack1[0] = eos;

	while (*expr)
	{
		token = gettoken(*expr);
		if (token == operand) 
		{
			do {
				postfix_expr[i++] = *expr;
				*expr++;
			} while ((*expr >= '0' && *expr <= '9') || *expr == '.' || *expr == 'a');
			postfix_expr[i++] = ' '; 

		}
		else if (token == lparen)
		{
			push1(token);
			*expr++;
		}
		else if (token == rparen)
		{
			precedence temp;
			temp = pop1();
			while (temp != lparen)
			{
				postfix_expr[i++] = getsymbol(temp);
				temp = pop1();
			}
			*expr++;
		}
		else
		{
			if (isp[stack1[top1]] >= icp[token])
			{
				while (isp[stack1[top1]] >= icp[token])
				{
					postfix_expr[i++] = getsymbol(pop1());
				}
				push1(token);
			}
			else
				push1(token);

			*expr++; 

			postfix_expr[i++] = ' '; 
		}

	}
	while (top1 != 0)
	{
		precedence temp;
		temp = pop1();
		postfix_expr[i++] = getsymbol(temp);
	}
	postfix_expr[i] = '\0';
	
	return postfix_expr;
}

void push1(precedence token)
{
	if (top1 > (MAX_STACK_SIZE - 1))
		printf("stack1 overflow\n");
	stack1[++top1] = token;
}

precedence pop1()
{
	if (top1 < 0)
		printf("stack1 underflow\n");
	return stack1[top1--];
}
//gettoken 
precedence gettoken(char symbol)
{
	switch (symbol)
	{
	case '(':
		return lparen;
	case ')':
		return rparen;
	case '+':
		return plus;
	case '-':
		return minus;
	case '*':
		return times;
	case '/':
		return divide;
	case '%':
		return mod;
	case '^':
		return square;
	default:
		return operand;
	}
}
//gettoken 
char getsymbol(char token)
{
	switch (token)
	{
	case lparen:
		return '(';
	case rparen:
		return ')';
	case plus:
		return '+';
	case minus:
		return '-';
	case times:
		return '*';
	case divide:
		return '/';
	case mod:
		return '%';
	case square:
		return '^';
	default:
		return '@';
	}
}

double calc(char *postfix_expr)
{
	double result = 0.0;
	while (*postfix_expr)
	{
		if ((*postfix_expr >= '0' && *postfix_expr <= '9') || *postfix_expr == 'a')
		{
			char temp[100];
			int i = 0;
			while (*postfix_expr != ' ')
			{
				if (*postfix_expr == 'a')
				{
					temp[i++] = '-';
					temp[i++] = '1';
				}
				temp[i++] = *postfix_expr++;
			}
			temp[i] = '\0';
		
			push2(atof(temp));
		}
		else if (*postfix_expr == ' ')
		{
			*postfix_expr++;
		}
		else
		{
			double pop2Value1;
			double pop2Value2;
			switch (*postfix_expr)
			{
			case '+':
				pop2Value1 = pop2();
				pop2Value2 = pop2();
				result = pop2Value2 + pop2Value1;
			
				break;
			case '-':
				pop2Value1 = pop2();
				pop2Value2 = pop2();
				result = pop2Value2 - pop2Value1;
		
				break;
			case '*':
				pop2Value1 = pop2();
				pop2Value2 = pop2();
				result = pop2Value2*pop2Value1;
	
				break;
			case '/':
				pop2Value1 = pop2();
				pop2Value2 = pop2();
				result = pop2Value2 / pop2Value1;

				break;
			case '%':
				pop2Value1 = pop2();
				pop2Value2 = pop2();
				result = fmod(pop2Value2, pop2Value1);
				break;
			case '^':
				pop2Value1 = pop2();
				pop2Value2 = pop2();
				result = pow(pop2Value2, pop2Value1);
				break;
			default:
				printf("Invalid expression\n");
				exit(0);
			}
			push2(result);
			*postfix_expr++;
		}
	}
	if (result == 0.0)
		result = pop2();
	return result;
}


void push2(double value)
{
	if (top2 > (MAX_STACK_SIZE - 1))
	{
		printf("Invalid Expression !\n");
		exit(1);
	}

	stack2[++top2] = value;

}

double pop2()
{
	if (top2 < 0)
	{
		printf("Invalid Expression !\n");
		exit(2);
	}

	return stack2[top2--];
}
