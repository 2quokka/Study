#include <stdio.h>

struct test {
	char a[10];
	int b;
};

int main(void)
{
	printf("size : %d \n", sizeof(struct test));  // 8
	// struct offset method => offsetof(struct name, member name)
	return 0;
}
