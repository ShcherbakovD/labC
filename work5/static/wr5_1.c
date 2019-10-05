#include <stdio.h>

#include "str_option.h"

#define STR_SIZE 128UL

int main(void) 
{
	char str[STR_SIZE] = "hello, ";
	str_connect(str, STR_SIZE, "dear friend");

	printf("%s\n", str);
//hello, dear friend

	char str2[STR_SIZE];
	str_divided(str2, STR_SIZE, str, 8);

	printf("%s, bye\n", str2);
//dear friend, bye
	return 0;
}
