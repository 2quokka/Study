//wordbookMain.c
#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "alphabet.h"

#define MAX_WORD_LENGTH 128
#define TRUE 1
#define FALSE 0

typedef unsigned char BOOL;
enum SELECT{ADD=1,SEARCH,DELETE,PRINT,EXIT};
void menu();
void enterWord(char *word);
void addWord(LinkedBinaryTree *book, char *word);
void searchForWord(LinkedBinaryTree *book, char *word);
void deleteWord(LinkedBinaryTree *book, char *word);
BOOL isDuplicate(char *word, LinkedBinaryTree *book){
void printWord();

char* checkForDuplicateAl(LinkedBinaryTreeNode *ptr, char *word, LinkedBinaryTree *book);

LinkedBinaryTree* book;

int main(void)
{
    char word[MAX_WORD_LENGTH]
    SELECT sel;
    menu(); // print menu
    sel = getchar();

    while(1)
    {
        switch(sel)
        {
            case ADD:
                enterWord(word);
                addWord(word, book);
            case SEARCH:
                enterWord(word);
                searchForWord(word, book);
            case DELETE:
                enterWord(word);
                deleteWord(word, book);
            case PRINT:
                printWord();
            case EXIT:
            case default:

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
    printf("5. EXIT\n");
    printf(": ");
}

void enterWord(char *word){
    printf("insert word : ");
    fgets(word);
    word[strlen(word)-1]='\0';
}

void addWord(LinkedBinaryTree *book, char* word){
    int len =strlen(word);
    int i;
    LinkedBinaryTreeNode *ptr = NULL;


    if(book == NULL)
    {
        book = createLBT();
        book->root = ptr = createLBTNode(createAlphabet(*word));
        
        for(i=1; i<len; i++)
        {
            createChildNode(ptr, createAlphabet(*(word+i)));
            ptr = ptr->child;
        }
    }

    else
    {
        if(isDuplicate(word, book))
        {
            printf("Duplicate !! \n");
            return;
        }

        ptr =book->root;

        while(ptr)
        {
            if(ptr->al->ch == *word)
            {
                ptr->al->count ++;
                word++;
                ptr=ptr->child;
            }
           else
           {
              ptr=ptr->brother;
           }
        }

        createBrotherNode(ptr, createAlphabet(*word));
        word++;
        ptr= ptr->brother;

        while(*word){
            createChildNode(ptr, createAlphabet(*word));
            ptr = ptr->child;
        }
    }
}
void searchForWord(LinkedBinaryTree *book, char* word){
         if(isDuplicate(word, book))
             printf("found word !!\n");
         else
             printf("sorry, word not found!! \n");
    }
void deleteWord(LinkedBinaryTree *book, char* word){}
void printWord(){}
BOOL isDuplicate(char *word, LinkedBinaryTree *book){
    char wch;
    LinkedBinaryTreeNode *ptr=book->root;

    while(ptr)
    {
        if(ptr->al->ch == *word)
        {
            word++;
            ptr = ptr->child;
        }
        else
            ptr = ptr->brother;
    }

    if(*word == '\0')
        return TRUE;
    else
        return FALSE;

}

char* checkForDuplicateAl(LinkedBinaryTreeNode *ptr, char *word, LinkedBinaryTree *book){
    char *alptr=word;
    if(book == NULL) //
        exit(-1);
    
    if(book->root == NULL)
        exit(-1);


   ptr = book->root;

    while(ptr)
    {
        if(ptr->al->ch == *alptr)
        {
            alptr = alptr+1;
            ptr=ptr->child;
        }
       else
       {
          ptr=ptr->brother;
       }
    }

     return alptr;// NULL is duplicate
}
       
