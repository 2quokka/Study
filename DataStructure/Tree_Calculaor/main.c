#include <stdio.h>
#include <string.h>
#include "Tree.h"

#define MAX 100

int main(void){
    char infix[MAX];
    printf("insert infix(exit Q): ");
    fgets(infix,MAX,stdin);
    infix[strlen(infix)-1]='\0';

    if(!strcmp(infix, "Q") || !strcmp(infix, "q"))
        return 0;

    toPostfix(infix);
    printf("%s\n",infix);

    return 0;
}

char* toPostfix(char *infix){

    int len = strlen(infix);
    char token, *expression = malloc(len+1);
    int index =0;
    LinkedBinaryTree *tree;

    strcpy(expression, infix);

    tree=createLBT()
    for(index=0;index < len; index ++)
    {
        token = expression[index];

        switch(token)
        {
            case '+':case'-':

            case '*':case'/':

            default:

        }
    }
    free(expression);
}
