#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#define STR_SIZE 1024

int main() {

    void *str_op_HAND = dlopen("libstr_option.so", RTLD_LAZY);
    if (str_op_HAND == NULL) {
        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        exit(1);
    }

    void (*conc)(char * restrict dest,
                 const size_t capacity_dest,
                 const char * restrict source) = dlsym(str_op_HAND, "str_connect");


    void (*gap)(char * restrict dest,
                const size_t capacity_dest,
                char * restrict source, int gap_from) = dlsym(str_op_HAND, "str_divided");


    char str[STR_SIZE] = "hello, ";
    (*conc)(str, STR_SIZE, "dear friend");
    printf("%s\n", str);


    char str2[STR_SIZE];
    (*gap)(str2, STR_SIZE, str, 8);
    printf("%s, bye\n", str2);

    dlclose(str_op_HAND);

    return 0;
}
