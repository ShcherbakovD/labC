//////////////////////////////////////////
// Оставить строки, не содержащие цифры //
//   Параметры командной строки:        //
//	1. Имя входного файла          		//
//  2. Количество обрабатываемых строк  //
//////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define FILENAME_SIZE 128
#define BUFF_SIZE 2056

int main(int argc, char *argv[])
{
    FILE *fpIn;

    if (argc < 3)
    {
        fprintf (stderr, "Недостаточное количество аргументов. <Имя входного файла ><Количество обрабатываемых строк> \n");
        exit(1);
    }

    if((fpIn = fopen(argv[1], "r")) == NULL)
    {
        printf("Файл %s невозможно открыть\n", argv[1]);
        exit(1);
    }

    int paramStr = atoi(argv[2]);
    char fileName[FILENAME_SIZE];
    char newFileName[FILENAME_SIZE];
    strcpy(fileName, argv[1]);
    int i=0;
    while (fileName[i]!='.')
    {
        newFileName[i]=fileName[i];
        i++;
    }
    strcat(newFileName, ".from");

    FILE *fpOut = fopen(newFileName, "w");

    int strWithNum;
    char buffer[BUFF_SIZE];
    int count = 0;
    while ((count != paramStr))
    {
        strWithNum = 0;
        fgets(buffer, BUFF_SIZE, fpIn);

        for (size_t i = 0; buffer[i] != '\n'; i++)
        {
            if (isdigit(buffer[i]))
                strWithNum = 1;
        }

        if (!strWithNum && !feof(fpIn)) {
            fputs(buffer, fpOut);
        }
        count++;
    }

    if(fclose(fpIn))
    {
        printf("Ошибка при закрытии файла\n");
        exit(1);
    }

    if(fclose(fpOut))
    {
        printf("Ошибка при закрытии файла\n");
        exit(1);
    }
    return 0;
}
