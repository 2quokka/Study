#include <stdio.h>
#include <string.h>
#include <ctype.h>


void change_case(char *str);

int main(int argc, char *argv[]){
	int i;
	char str[128];
	
	if(argc < 2)
	{
		printf("%s string \n",argv[0]);
		return 0;
	}

	strcpy(str, argv[argc-1]);

	for(i=argc-2; i>0; i--)
	{
		strcat(str," ");
		strcat(str,argv[i]);
	}	

	change_case(str);
	puts(str);

	return 0;

}

void change_case(char *str)
{
	int i=0;
	while(*(str+i))
	{
		if(isupper(*(str+i)))
			*(str+i) = tolower(*(str+i));
			
		else if(islower(*(str+i)))
			*(str+i) = toupper(*(str+i));
		
		i++;
	}
}

