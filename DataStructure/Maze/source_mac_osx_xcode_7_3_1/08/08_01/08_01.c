#include <stdio.h>

int factorial(int n);

int main()
{
    int input_value = 3;
    int result = 0;
    
    result = factorial(input_value);
    printf("%d! = %d\n", input_value, result);
    
    return 0;
}

int factorial(int n)
{
    int ret = 0;
    if (n <= 1)
    {
        ret = 1;
    }
    else
    {
        ret = n * factorial(n - 1);
    }
    return ret;
}
