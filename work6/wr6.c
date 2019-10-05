#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void inverse(char symbles[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(symbles) - 1; i < j; i++, j--) {
        c = symbles[i];
        symbles[i] = symbles[j];
        symbles[j] = c;
    }
}
void itoa(int n, char symbles[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        symbles[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        symbles[i++] = '-';
    symbles[i] = '\0';
    inverse(symbles);
}

int main(int argc, char *argv[]) {
    int i, pid[argc], status, stat;
    const int BUFF_SIZE = 1024UL;
    char buffer[BUFF_SIZE];
    char bufferi[BUFF_SIZE];
    char bufferNext[BUFF_SIZE];
    if (argc < 2) {
        printf("Мало аргументов: Введите <test.txt> <test.txt> ....\n");
        exit(-1);
    }
    for (i = 1; i < argc; i++) {

        pid[i] = fork();
        srand(getpid());

        if (-1 == pid[i]) {
            perror("fork");
            exit(1);
        } else if (0 == pid[i]) {
            printf(" CHILD: Это %d процесс-потомок PID : %d СТАРТ! ", i, getpid());
            sleep(rand() % 4);
            FILE *fp;
            if ((fp = fopen((argv[i]), "r")) == NULL) {
                printf
                ("Не удается открыть файл.\n");
            } else {
                FILE *fin;
                char c;
                int summ = 0;
                while ((c = fgetc(fp)) != EOF) {
                    summ += (int)c;
                }
                itoa(getpid(), buffer);
                strcat(buffer, " ");
                itoa(summ, bufferNext);
                strcat(buffer,bufferNext);
                strcat(buffer, "\n");
                itoa (i,bufferi);
                if ((fin = fopen(bufferi, "w")) == NULL) {
                    printf
                    ("Не удается открыть файл.\n");
                }
                fputs(buffer, fin);
                printf(" ---------> ВЫХОД!\n");
                sleep(4);
                if(fclose(fin)) {
                    printf
                    ("Ошибка при закрытии файла.\n");
                    exit(1);
                }
                if(fclose(fp)) {
                    printf
                    ("Ошибка при закрытии файла.\n");
                    exit(1);
                }
                exit(0);
            }
        }
    }
    printf("PARENT: Это процесс-родитель!\n");
    for (i = 1; i < argc; i++) {

        status = waitpid(pid[i], &stat, 0);
        if (pid[i] == status) {
            FILE *fin;
            const int BUFF_SIZE = 1024;
            itoa (i,bufferi);
            if (NULL == (fin = fopen(bufferi, "r"))) {
                printf
                ("File  cannot open.\n");
            }
            fgets(buffer, BUFF_SIZE, fin);

            char *red = strtok(buffer, " ");
            int pid1 = atoi(red);

            red = strtok(NULL, " ");
            int result = atoi(red);
            printf
            ("Процесс-потомок %d done RESULT %d(файл %d)\n",
             pid1, result, i);
            if(fclose(fin)) {
                printf
                ("Ошибка при закрытии файла.\n");
                exit(1);
            }
        }
    }
    sleep(3);
    printf ("Зачистить следы?\n1) -> да\n2) -> нет\n");
    printf ("Ответ : ");
    int otvet;
    scanf("%d",&otvet);
    switch (otvet) {
    case 1:
        for (i = 1; i < argc; i++) {
            itoa (i,bufferi);
            printf ("Удаление файлов дочерего процесса : ");
            sleep(2);
            if (-1 == remove (bufferi))
                printf ("Ошибка\n");
            else
                printf ("Выполнено\n");
        }
        break;
    case 2:
        break;
    }
    return 0;
}
