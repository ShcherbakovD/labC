///////////////////////////////////////////////
//	После каждой точки вставить символ ‘\n’  //
// 	 Параметры командной строки:             //
//		  1. Имя входного файла              //
//		  2. Количество вставок              //
///////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1024
#define NAME_SIZE 128

void modernString(int count, char *str, FILE *fp) {

    char name[NAME_SIZE];
    int i = 0;
    while (*str != '.')
        name[i++] = *str++;
    name[i++] = '.';
    name[i] = 'c';
    FILE *fd;
    fd = fopen(name, "w");
    char ch, specch='\n';
    int founden = 0;
    while ((ch=fgetc(fp)) != EOF) {
        fputc(ch, fd);
        if (ch == '.' && founden < count) {
            fputc(specch, fd);
            founden++;
        }
    }
    if(fclose(fd)) {
        printf("Ошибка при закрытии файла.\n");
        exit(1);
    }
}
int main(int argc, char *argv[]) {
    FILE *f;
    if (argc < 3) {
        fprintf (stderr, "Мало аргументов. Используйте <имя файла> <число вставок>\n");
        exit (1);
    }
    if((f=fopen(argv[1], "r"))==NULL) {
        printf("Не удается открыть файл.\n");
        exit(1);
    }
    int count = atoi(argv[2]);
    modernString(count, argv[1], f);
    if(fclose(f)) {
        printf("Ошибка при закрытии файла.\n");
        exit(1);
    }
    return 0;
}
