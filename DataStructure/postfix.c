#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define TRUE 1
#define FALSE 0

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand}precedence;

void postfix();
int eval();
precedence getToken(char *symbol, int *n);
char printToken(precedence token);


char expr[MAX_LEN]; // ����
int cipher[MAX_LEN] = {0};
int cipher_index = 0;

precedence stack[MAX_LEN];
int top = -1;

void push(precedence token);
precedence pop();
void stackInit() { top = -1; }

int main()
{
	char buf[MAX_LEN];

	printf("insert : ");
	fgets(buf, MAX_LEN, stdin);
	buf[strlen(buf) - 1] = '\0';
	strcpy(expr, buf);

	postfix();
	printf("after convert : %s \n", expr);
	printf("result : %d \n ", eval());
	return 0;
}

int eval() // ���� ǥ��� ���
{
	precedence token;
	char symbol;
	int op1, op2;
	int i, n = 0;
	char number[20] = { 0 };

	cipher_index = 0; //�ڸ��� �ε��� �ʱ�ȭ

	stackInit(); //�����ʱ�ȭ

	token = getToken(&symbol, &n);
	
	while (token != eos) {
		if (token == operand)
		{
			for (i = 0; i < cipher[cipher_index]; i++)
			{
				number[i] = symbol;
				token = getToken(&symbol, &n); //*symbol = expr[(*n)++];
			}
			push(atoi(number));

			memset(number, 0, 20);
			cipher_index++;
			continue;
		}
		else {
			op2 = pop();
			op1 = pop();

			switch (token) {
				case plus:	push(op1 + op2);
							break;
				case minus: push(op1 - op2);
							break;
				case times: push(op1 * op2);
							break;
				case divide: push(op1 / op2);
							break;
				case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

void postfix() // ���� -> ����  expr
{
	int isp[] = { 0,19,12,12,13,13,13,0 };
	int icp[] = { 20,19,12,12,13,13,13,0 };
	char symbol; // �����ڿ� �ǿ�����
	precedence token; //������ �ϸ��
	int n = 0; //������ �ε���
	char buf[MAX_LEN];  //�ϼ��� ����ǥ����� ���� �ӽð���
	int buf_index = 0;

	int op_flag = TRUE;  //�ʱⰪ true

	top = 0;
	stack[0] = eos;
	

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand) {
			buf[buf_index++] = symbol;
			if (op_flag)  //true
			{
				cipher[cipher_index]++;
			}
			else  //false
			{
				cipher[++cipher_index]++;
				op_flag = TRUE;
			}
		}
		else if (token == rparen) {
			op_flag = FALSE;
			while (stack[top] != lparen)
				buf[buf_index++] = printToken(pop());
			pop();
		}
		else {
			op_flag = FALSE;
			while (isp[stack[top]] >= icp[token])
				buf[buf_index++] = printToken(pop());
			push(token);
		}
	}

	while ((token = pop()) != eos)
		buf[buf_index++] = printToken(token);

	buf[buf_index] = '\0';  //buf ���ڿ��� ������ 

	strcpy(expr,buf);  //buf->expr ����
}

char printToken(precedence token)
{
	switch (token){
	case lparen:return '(';
	case rparen: return ')';
	case plus: return '+';
	case minus: return '-';
	case divide: return '/';
	case times: return '*';
	case mod: return '%';
	case eos: return ' ';
	default: return -1;

	}
}
precedence getToken(char *symbol, int *n) // �ɺ� �ʱ�ȭ�� �ϸ���� �����
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0':
	case ' ': return eos;
	default: return operand;
	}
}

void push(precedence token)
{
	if (top >= MAX_LEN - 1)
	{
		printf("stack is full\n");
		return;
	}
	stack[++top] = token;
}
precedence pop()
{
	if (top == -1)
	{
		printf("stack is empty! \n");
		return eos;
	}
	return stack[top--];
}
