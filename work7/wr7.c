#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf
        ("Мало аргументов. Используйте <кол-во шахтеров> <кол-во ресурсов>\n");
        exit(-1);
    }


    int miners = atoi(argv[1]);
    int pid[miners];
    int fd[miners][2];
    srand(time(NULL));

    int mine=atoi(argv[2]);
    int len=(rand() % mine + 1);
    for (int i = 1; i <= miners; i++) {
        
        pipe(fd[i]);
        pid[i] = fork();
        srand(getpid());

        if (-1 == pid[i]) {
			
            perror("fork");
            exit(1);
        
        } else if (0 == pid[i]) {
        
            close(fd[i][0]);

            while (1) {
        
                write(fd[i][1], 0, sizeof (int));
                sleep(rand() % 2);
                write(fd[i][1], &len, sizeof (int));
        
            }
        
            exit(1);
        }
    }
    system("clear");
    printf("Кол-во ресурсов в данной локации: %d \n", mine);
    while (1) {
		
        for (int i = 1; i <= miners; i++) {
        
            //для исключения вывода отрицательного числа ресурсов
            //если не интерсно смотреть на отрицательные оставшиеся ресурсы
            //if (mine <= 0 || mine < len) {
            if (mine <= 0) {
        
                for (int i = 1; i <= miners; i++) {
        
                    kill(pid[i], SIGKILL);
        
                }
        
                return 0;
        
            }

            read(fd[i][0], &len, sizeof (int));
            mine = mine - len;
            printf
            ("Юнит [%d] кричит : Осталось %d реcурсов\n",
             i, mine);
             
        }
    }
    return 0;
}
