#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1024

int inp_str(char *string, int maxlen) {
    char buffer[MAX_LEN];
    scanf("%[^\n]", buffer);
    getchar();
    strncpy(string, buffer, maxlen);
    size_t len = strlen(buffer);
    return (int)len;
}

int inp_str2(char**string, int maxlen) {
    char buffer[MAX_LEN];
    char bufflen[MAX_LEN];
    sprintf(bufflen, "%%%ds", maxlen);
    scanf(bufflen, buffer);
    size_t len = strlen(buffer);
    *string = (char *)malloc(sizeof(char)*len);
    strcpy(*string, buffer);
    return (int)len;
}
char** readMas(int count, char **mas, int maxlen) {
    for (int i = 0; i < count ; i++) {
        mas[i] = (char *)malloc(sizeof(char)*maxlen);
        inp_str(mas[i], maxlen);
    }
    return mas;
}

void printMas(char **mas, int count) {
    for (int i = 0; i < count ; i++) {
        printf("%s\n", mas[i]);
    }
}

void freeMas(char **mas, int count) {
    for (int i = 0; i < count; i++) {
        free(mas[i]);
    }
    free(mas);
}

int getNumberWord(char *str) {
    int words = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i]==' ') {
            words++;
        }
    }
    words++;
    return words;
}

int bubleSort(char **mas, int n) {
    int c = 0;
    int d = 0;
    int swichcount = 0;
    char *swap;
    for (c = 0 ; c < ( n - 1 ); c++) {
        for (d = 0 ; d < n - c - 1; d++) {
            if (getNumberWord(mas[d+1]) > getNumberWord(mas[d])) {
                swap     = mas[d];
                mas[d]   = mas[d+1];
                mas[d+1] = swap;
                swichcount++;
            }
        }
    }
    return swichcount;
}

int main(int argc, char **argv) {
    char **mas = NULL;
    int count ;
    //printf("Введите кол-во строк:");
    scanf("%d", &count);
    getchar();
    mas = (char **)malloc(sizeof(char *)*count);
    mas = readMas(count, mas, MAX_LEN);
    int swichcount = bubleSort(mas, count);
    printf("\nРезультат сортировки :\n-----------------------\n");
    printMas(mas, count);
    printf("-----------------------\nКол-во перестановок:");
    printf("%d\n", swichcount);
    printf("Максимальное кол-во слов в массиве строк :");
    printf("%d\n", getNumberWord(mas[0]));
    freeMas(mas, count);
}
