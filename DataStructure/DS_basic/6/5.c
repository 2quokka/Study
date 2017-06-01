#include <stdio.h>
#include <string.h>

int main(){

	char word[30];
	int i;

	printf("insert :"); scanf("%s", word);

	i= strlen(word)-1;

	for(;i>=0;i--)
		putchar(*(word+i));

	puts("");
	
	return 0;
}
