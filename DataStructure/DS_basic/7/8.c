#include <stdio.h>
#include <string.h>


int myStrlen(char *);
int myStrcmp(char *, char *);

int main(){

	char str1[128] = "Welcome Network lab!";
	char str2[128] = "Nice to meet you!";


	printf("str1 = %s \n", str1);
	printf("str2 = %s \n", str2);

	printf("str1 len = %d \n", myStrlen(str1));
	
	if(myStrcmp(str1, str2) ==0)
		printf("str1 str2 equal! \n");
		else
			printf("different ! \n");

	puts("");

	printf("str1 str2 copying....\n");
	strcpy(str1,str2);

	
	printf("str1 = %s \n", str1);
	printf("str2 = %s \n", str2);

	
	if(myStrcmp(str1, str2) ==0)
		printf("equal! \n");
		else
			printf("different ! \n");

	return 0;
}

int myStrlen(char *str){
	int i=0;

	while( *(str+i) != 0)
		i++;

		return i;
}

int myStrcmp(char *str1, char* str2)
{
	int i=0;
	int result =-1;

	while(*(str1+i) == *(str2+i))
	{
		if(*(str1+i)==0)
		{
			result =0;
			break;
		}
		i++;
	}

	return result;
}
