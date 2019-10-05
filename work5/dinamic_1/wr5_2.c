#include <stdio.h>
#include "./str_option.h"
#define STR_SIZE 1024

int main() {
    char str[STR_SIZE] = "hello, ";
    str_connect(str, STR_SIZE, "dear friend");
    printf("%s\n", str);

    char str2[STR_SIZE];
    str_divided(str2, STR_SIZE, str, 8);
    printf("%s, bye\n", str2);

    return 0;
}
