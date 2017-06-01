#include "alphabet.h"

alphabet* createAlphabet(char ch)
{
    alphabet *al = malloc(sizeof(alphabet));

    alphabet->ch = ch;
    count = 1;

    return al;
}
void deleteAlphabet(alphabet *al){
    if(al != NULL){free(al);}}
