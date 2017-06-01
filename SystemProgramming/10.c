#include <stdio.h>

void encode(char *src, char *key, char *result); 
void decode(char *src, char *key, char *result);

void main(void) {     
	char *key = "123";     
	char *data = "I am a boy";     
	char result1[100];     
	char result2[100];
	encode(data, key, result1);     
	printf("%s가 %s로 엔코딩됨\n", data, result1); 
	decode(result1, key, result2);     
	printf("%s가 %s로 디코딩됨\n", result1, result2); }

	void encode(char *src, char *key, char *result)
	 {     
		 		while(*src) 
							*result++ = *src++ ^ *key++; 
							   	 *result = '\0'; 
	 }
	 void decode(char *src, char *key, char *result) 
	 { 
		 		encode(src, key, result); 
	 }
