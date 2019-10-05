#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 1024


struct cashGame {
    char nameOfTeam[MAX_LEN];
    char nameOfGame[MAX_LEN];
    int points;
    int fund;
};

typedef struct cashGame cashGames;

void readCash(cashGames *cG) {
    printf("Введите Команду:");
    scanf("%s", cG->nameOfTeam);
    printf("Введите Игру:");
    scanf("%s", cG->nameOfGame);
    printf("Введите Очки:");
    scanf("%d", &cG->points);
    printf("Введите Призовой Фонд:");
    scanf("%d", &cG->fund);
}

static int cmp(const void *p1, const void *p2) {
    cashGames * st1 = *(cashGames**)p1;
    cashGames * st2 = *(cashGames**)p2;
    return st1->fund - st2->fund;
}

void printCash(cashGames *cG) {

    printf("Команда: %s  ", cG->nameOfTeam);
    printf("Игра: %s  ", cG->nameOfGame);
    printf("Очки: %d  ", cG->points);
    printf("Призовой Фонд: %d  \n", cG->fund);

}

int main(int argc, char **argv) {
    int count;
    printf("Введите количество сделавших ставку: ");
    scanf("%d", &count);
    cashGames** cG = (cashGames**)malloc(sizeof(cashGames*)*count);
    for (int i = 0; i < count ; i++) {
        cG[i] = (cashGames*) malloc (sizeof(cashGames));
        readCash(cG[i]);
    }
    printf("\n");
    system ("clear");
    printf("Количество сделавших ставку: %d\n" , count);
    qsort(cG, count, sizeof(cashGames*), cmp);
    for (int i = 0; i < count ; i++) {
		printf("%d) " , i+1);
        printCash(cG[i]);
    }
    for (int i = 0; i < count; i++)
    {
        free(cG[i]);
    }
    free(cG);
    return 0;
}

