#include <stdio.h>

typedef unsigned char BYTE;

int main()
{
	BYTE byte=0x0A;

	printf("%d \n",byte);
	printf("BYTE size  = %u\n", sizeof(byte));
	
	return 0;
}
