#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "WordTree.h"
#define MAX 256

typedef enum{ADD=1, SEARCH, DELETE, PRINT, SORT, EXIT}SELECT;

TreeNode* addWord(TreeNode **root, char *word, char *meaning, int len, int index);
void menu();
void printWord(TreeNode *root, char *string);
void deleteWord(TreeNode **root, char *word);
void searchWord(TreeNode *root, char *word);
void sort(TreeNode *root);
void sort_level(TreeNode *root);


TreeNode *root;


int main(void)
{
    char word[MAX], meaning[MAX];
    SELECT sel;

    while(1)
    {
        menu();
        scanf("%d", &sel);
        getchar();

        switch(sel)
        {
            case ADD:
                printf("word : ");
                fgets(word, MAX, stdin);
                word[strlen(word)-1]= '\0';

                printf("meaning : ");
                fgets(meaning, MAX, stdin);
                meaning[strlen(meaning)-1]= '\0';

                addWord(&root,word,meaning,strlen(word), 0);
                printf("complete!!  \n");
                break;
            case SEARCH:
                printf("word : ");
                fgets(word, MAX, stdin);
                word[strlen(word)-1]= '\0';

                searchWord(root, word);
                break;
            case DELETE:
                printf("word : ");
                fgets(word, MAX, stdin);
                word[strlen(word)-1]= '\0';

                deleteWord(&root, word);
                break;
            case PRINT:
                printf("print \n\n");
                printWord(root,NULL);
                break;
            case SORT:
                printf("sort \n\n");
                sort(root);
                break;
            case EXIT:
                return 0;
                break;
        }
    }

    return 0;
}

void menu(){
    printf("\n========MENU=======\n");
    printf("1. ADD\n");
    printf("2. SEARCH\n");
    printf("3. DELETE\n");
    printf("4. PRINT\n");
    printf("5. SORT\n");
    printf("6. EXIT\n");
    printf(": ");
}

TreeNode* addWord(TreeNode **root, char *word, char *meaning, int len, int index)
{
    if(index > len)
        return NULL;
    else
    {
        if(*root != NULL)
        {
            if((*root)->alphabet != word[index])
            {
                addWord(&((*root)->brother), word, meaning, len, index);
            }
            else
            {
                if(index == len-1)
                {
                    if((*root)->meaning == NULL)
                    {
                        (*root)->meaning = malloc(strlen(meaning)+1);
                        strcpy((*root)->meaning, meaning);
                    }
                    else
                    {
                        printf("override word ! \n");
                        return NULL;
                    }
                }
                else
                    addWord(&((*root)->child), word, meaning, len, index+1);
            }
        }
        else
        {
            if(index == len-1)
            {
                makeTreeNode(root, word[index], meaning);
            }
            else
            {
                makeTreeNode(root, word[index], NULL);
                addWord(&((*root)->child), word, meaning, len, index+1);
            }
        }
    }

    return *root;
}

void printWord(TreeNode *root, char *string)
{
    char temp[MAX];
    char *temptr = temp;

    memset(temp,0,MAX);

    if(string != NULL)
    {
       strcpy(temp,string);
       temptr = temp + strlen(temp);
    }

    if(root->meaning != NULL)
    {
        printf("%s", temp);
        putchar(root->alphabet);
        printf(" : %s \n", root->meaning);
    }

    if(root->brother != NULL)
    {
        printWord(root->brother, temp);
    }

    if(root->child != NULL)
    {
        *temptr=root->alphabet;
        *(temptr+1)='\0';
        printWord(root->child, temp);
    }
}
void deleteWord(TreeNode **root, char *word){
    TreeNode *temp= NULL;

    if(*root != NULL)
    {
        if((*root)->alphabet == *word)
        {
            if(*(word+1) =='\0' && (*root)->meaning != NULL)
            {
                if((*root)->child != NULL)
                {
                    free((*root)->meaning);
                    (*root)->meaning = NULL;
                }
                else
                {
                    temp = (*root)->brother;
                    free((*root)->meaning);
                    free(*root);
                    *root = temp;
                    return;
                }
            }
            else
            {
                deleteWord(&((*root)->child), word+1);
            }

            if((*root)->child == NULL && (*root)->meaning == NULL)
            {
                temp = (*root)->brother;
                free(*root);
                *root = temp;
            }
        }
        else
        {
            deleteWord(&((*root)->brother), word);
        }
    }
}

void searchWord(TreeNode *root, char *word){
    int i=0;
    TreeNode *tmp = root;

    while(tmp)
    {
        if(tmp == NULL)
        {
            return;
        }

        if(tmp->alphabet == *(word+i))
        {
            ++i;

            if(*(word+i) == '\0' && tmp->meaning !=NULL)
            {
                printf("%s : %s \n\n", word, tmp->meaning);
                return;
            }
            else
                tmp = tmp->child;
        }
        else
        {
            tmp = tmp->brother;
        }
    }
    
    printf("search fail ! \n");
}

void sort(TreeNode *root){

    TreeNode *ptr = NULL;

    if(root == NULL)
        return;

    sort_level(root);

    while(root)
    {
        ptr=root->child;
        while(ptr)
        {
            sort_level(ptr);
            ptr=ptr->child;
        }
        root=root->brother;
    }
}

void sort_level(TreeNode *root){
    int i=0,j=0;
    TreeNode *tmp = NULL;
    TreeNode *ptr = root;

    while(ptr->brother)
    {
        if(ptr->alphabet > ptr->brother->alphabet)
        {
            tmp=ptr->brother->brother;
            ptr->brother->brother=ptr;
            ptr->brother=tmp;
        }

        i++;
    }

    while(i>1)
    {
        ptr = root;
        for(j=0; j<i-1; j++)
        {
            if(ptr->alphabet > ptr->brother->alphabet)
            {
                tmp=ptr->brother->brother;
                ptr->brother->brother=ptr;
                ptr->brother=tmp;
            }
        }
        i--;
    }
}
