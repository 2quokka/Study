#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int menu();
int add(int a, int b);
int sub(int a, int b);
int divd(int a, int b);
int mul(int a, int b);


int main(void)
{
    int a, b, ch;
    int result=0;

    printf ("두개의 값을 입력하시오 : ");
    scanf("%d %d",&a, &b);

while(1)
{
    ch = menu(); //메뉴 선택함수

    switch(ch)
    {
		case 1:
	    	result = add(a, b);
	    	break;
		case 2:
	    	result= sub(a, b);
	    	break;
		case 3:
		    result= divd(a ,b);
		    break;
		case 4:
		    result= mul(a, b);
		    break;
		case 5:
		    puts("프로그램 종료 ");
	 	    return 0;
		default:
	   		puts("잘못된 입력입니다. ");
	    	continue;
    }
    break;
}
    
    printf("결과값은 %d 입니다 \n", result);

    return 0;
}

int menu(){

    char op[10];
    int ch=0;
    printf("choice operator (add, subtract, multiply, divide, quit) : ");
    scanf("%s",op);

    if(strcmp(op,"add")==0)
	ch=1;
    else if(strcmp(op,"subtract")==0)
	ch=2;
    else if(strcmp(op,"divide")==0)
	ch=3;
    else if(strcmp(op,"multiply")==0)
	ch=4;
    else if(strcmp(op,"quit")==0)	
	ch=5;

    return ch;
}
int add(int a, int b){return a+b;}
int sub(int a, int b){return a-b;}
int divd(int a, int b){
	if(b==0)
		printf("not devided! \n");
	return a/b;}
int mul(int a, int b){return a*b;}
