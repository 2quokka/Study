#include <stdio.h>
#include <string.h>

int main(){

	char str[128]="Hello";
	char tmp[128];
	
	printf("%s \n",str);

	//strlen
	printf("strlen : %d\n",strlen(str));
	
	//gets
	printf("gets : ");
	gets(tmp); // overflow warnning 

	//puts
	printf("puts : ");
	puts(tmp);

	//strcmp
	printf("strcmp : %d\n", strcmp(str,tmp));

	//strcat
	printf("strcat : ");
	strcat(str, tmp);
	puts(str);

	return 0;
}
