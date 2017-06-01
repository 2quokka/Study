#include <stdio.h>

int factorial_iter(int n);

int main()
{
    int input_value = 3;
    int result = 0;
    
    result = factorial_iter(input_value);
    printf("%d! = %d\n", input_value, result);
    
    return 0;
}

int factorial_iter(int n) {
    int ret = 1;
    int i = 1;
    
    for(i = n; i > 1; i--) {
        ret = ret * i;
    }
    
    return ret;
}