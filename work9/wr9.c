#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, const char *argv[]){
    
    int  count = 10;
    float *s, summ = 0, shmid, *shm;
    float data1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float data2[] = {0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};  
    if (argc < 2){
		fprintf (stderr, "Используйте %s <число>\n", argv[0]);
		exit (1);
	}
	
    sscanf(argv[1], "%d", &count);
    
    int size = sizeof(int)*count;
    
    /* Создадим область разделяемой памяти */
    if ((shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /* Получим доступ к разделяемой памяти */
    if ((shm = shmat(shmid, NULL, 0)) == (float *) -1) {
        perror("shmat");
        exit(1);
    }

    /* Запишем в разделяемую память */
	s = shm;
	for (int i = 0; i < count; i++){
		s[i] = data1[i]*data2[i]; //*s++ = i;
		printf("%f * %f = ", data1[i], data2[i]);
		printf("%f\n",s[i]);	
	}
	
	pid_t pid;
	pid = fork();
	if (0 == pid) {

		/* Прочитаем из разделяемой памяти */
		s = shm;
		printf("Мат.ожидание \n");
		for (int i = 0; i < count; i++){
			summ=+s[i];
			printf("%f\n",summ);
		}	
		printf("%f", summ);
		if (shmdt(shm) < 0) {
			printf("Ошибка отключения\n");
			exit(1);
		} 
		exit(0);
		
	} else if (pid < 0){
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	}	
	
	wait(NULL);
	
	/* Удалим созданные объекты IPC */	
	 if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("Невозможно удалить область\n");
		exit(1);
	}
    exit(0);

}
