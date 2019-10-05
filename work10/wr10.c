#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MAX_LEN 1024UL

char *sym;

struct {
	pthread_mutex_t mutex;
}

shared = {
	PTHREAD_MUTEX_INITIALIZER};

void *founder(void *);

int main(int argc, char *argv[])
{
	int result;
	FILE *find_proj;
	int N;
	sym = (char *)malloc(sizeof (char) * MAX_LEN);
	int consilience = 0;

	if (argc < 3) {
		printf("Введите <имя файла> <кол-во обрабатываемых строк> <строку поиска>\n");
		exit(1);
	}
	N=atoi(argv[2]);
	for (int i = 3; i < argc; i++) {
		strcat(sym, argv[i]);
		if (i - argc != -1)
			strcat(sym, " ");
	}
	char *pos;
	if ((pos = strchr(sym, '\n')) != NULL)
		*pos = '\0';


	if ((find_proj = fopen(argv[1], "r")) == NULL) {
		printf("Не удается открыть файл.\n");
		exit(1);
	}
	pthread_t threads[N];
	void *status[N];

	for (int i = 0; i < N; i++) {
		result = pthread_create(&threads[i], NULL, founder, find_proj);
		if (result != 0) {
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < N; i++) {
		result = pthread_join(threads[i], &status[i]);
		if (result != 0) {
			perror("Joining the first thread");
			return EXIT_FAILURE;
		} else {
			if (*((int *)status[i]) == 1)
				consilience++;
		}
		free(status[i]);
	}

	printf("Cовпадений : %d\n", consilience);
	if (fclose(find_proj)) {
		printf("Ошибка при закрытии файла.\n");
		exit(1);
	}

	return EXIT_SUCCESS;
}

void *founder(void *arg)
{
	int *working = (int *)malloc(sizeof (int));
	FILE *op = (FILE *) arg;
	int founed;
	char buffer[MAX_LEN];
	pthread_mutex_lock(&shared.mutex);
	fgets(buffer, MAX_LEN, op);
	char *pos;
	if ((pos = strchr(buffer, '\n')) != NULL)
		*pos = '\0';
	founed = strcmp(buffer, sym);
	if (founed == 0) {
		*working = 1;
	} else {
		*working = 0;
	}
	pthread_mutex_unlock(&shared.mutex);
	pthread_exit((void *)working);
}

