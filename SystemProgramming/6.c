#include <stdio.h>

#define SET_BIT(n, pos) ((n) |= ((1) << (pos)))
#define CLR_BIT(n, pos) ((n) &= (~(1) << (pos)))
#define GET_BIT(n, pos) ((n) == ((n) | ((1) << (pos))))

void display_bit(int value)
{
		int i;
			for (i = 31; i >= 0; i--)
					{
								if (GET_BIT(value, i))
												printf("1");
														else
																		printf("0");
																			}
																					printf("\n");
}

int main()
{
		int n;
			printf("정수값을 입력하시오:");
				scanf("%d", &n);

					display_bit(n);

						return 0;
}
