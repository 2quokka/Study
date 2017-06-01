#ifndef ALPHABET_H
#define ALPHABET_H

typedef struct alphabet{
    char ch;    
    int count;
}alphabet;

alphabet* createAlphabet(char ch);
void deleteAlphabet(alphabet *al);

#endif
