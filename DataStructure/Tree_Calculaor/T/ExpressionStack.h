
#ifndef EXPRESSION_STACK
#define EXPRESSION_STACK

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE  100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, square, eos, operand } precedence;

char * infix(char *);      //���� ǥ��� ���� 
char * postfix(char *);    //���� ǥ����� ���� ǥ������� ��ȯ 
double calc(char *);       //���� ǥ����� ���  
precedence gettoken(char); //�����ڸ� �̿��Ͽ� token�� ����  
char getsymbol(char);     //token�� �̿��Ͽ� �����ڸ� ����  
void push1(precedence);    //postfix �Լ����� stack1�� �����ڸ� push
precedence pop1();   //postfix �Լ����� stack1���� �����ڸ� pop
double calc(char *);  //���� ǥ��� ������ �Է¹޾� ����Ͽ� ����� ���� 
void push2(double);   //calc �Լ����� stack2�� ����/�����  push
double pop2();    //calc �Լ����� stack2�� ����/����� push
char* deleteSpace(char*);  //�Է¹��� ������ ������ ����

#endif
