#include <stdio.h>
#include <string.h>
#define CASE_CHANGE(a) ((a) ^= (32))

int main(void) { char s[100]; int i;
printf("문자열을 입력하시오: "); scanf("%s", s);
for(i=0;i<strlen(s);i++){
	CASE_CHANGE(s[i]);
} printf("결과 문자열: %s\n", s); return 0;
}
