#include "WordTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TreeNode** makeTreeNode(TreeNode **ptr, char alphabet, char *meaning)
{
    *ptr = malloc(sizeof(TreeNode));
    if(*ptr == NULL)
    {
        printf("memory allocation fail ! \n");
        exit(-1);
    }

    (*ptr)->alphabet = alphabet;
    
    if(meaning != NULL)
    {
        (*ptr)->meaning = malloc(strlen(meaning)+1);
        strcpy((*ptr)->meaning, meaning);
    }
    else
        (*ptr)->meaning = meaning;
        
    (*ptr)->brother =NULL;
    (*ptr)->child = NULL;

    return ptr;
}

void removeTreeNode(TreeNode *ptr)
{
    if(ptr != NULL){
        removeTreeNode(ptr->child);
        removeTreeNode(ptr->brother);
        printf("%s remove!! \n", ptr->meaning);
        
        if(ptr->meaning !=NULL)
            free(ptr->meaning);

        free(ptr);
    }
}
