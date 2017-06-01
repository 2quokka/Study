#include <stdio.h>

int main(){

	int i;

	for(i=1; i<1001; i++)
	{

		if(i%19==0)
			printf("%d\n", i);
	}

	return 0;
}
