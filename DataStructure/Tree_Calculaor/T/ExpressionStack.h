
#ifndef EXPRESSION_STACK
#define EXPRESSION_STACK

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE  100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, square, eos, operand } precedence;

char * infix(char *);      //중위 표기식 수정 
char * postfix(char *);    //중위 표기식을 후위 표기식으로 변환 
double calc(char *);       //후위 표기식을 계산  
precedence gettoken(char); //연산자를 이용하여 token을 구함  
char getsymbol(char);     //token을 이용하여 연산자를 구함  
void push1(precedence);    //postfix 함수에서 stack1에 연산자를 push
precedence pop1();   //postfix 함수에서 stack1에서 연산자를 pop
double calc(char *);  //후위 표기식 수식을 입력받아 계산하여 결과를 리턴 
void push2(double);   //calc 함수에서 stack2에 숫자/결과를  push
double pop2();    //calc 함수에서 stack2에 숫자/결과를 push
char* deleteSpace(char*);  //입력받은 수식의 공백을 제거

#endif
