#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

int main()
{
	int chld;
	struct sembuf P, V;
	union semun arg;
	int semid = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);

	P.sem_num = 0;
	P.sem_op = -1;
	P.sem_flg = SEM_UNDO;
	V.sem_num = 0;
	V.sem_op = 1;
	V.sem_flg = SEM_UNDO;
	arg.val = 1;

	if (semctl(semid, 0, SETVAL, arg) == -1)
	{
		perror("semctl setval error\n");
	}

	while ((chld = fork()) == -1);

	if (chld == 0)
	{
		for (int i = 0; i < 3; ++i)
		{
			sleep(1);
			semop(semid, &P, 1);
			printf("C");
			fflush(stdout);
			sleep(1);
			printf("c");
			fflush(stdout);
			semop(semid, &V, 1);
		}
		exit(0);
	}
	else
	{
		for (int j = 0; j < 3; ++j)
		{
			sleep(1);
			semop(semid, &P, 1);
			printf("P");
			fflush(stdout);
			sleep(1);
			printf("p");
			fflush(stdout);
			semop(semid, &V, 1);
		}
		wait(0);
		semctl(semid, IPC_RMID, 0);
	}
	printf("\n");
	return 0;
}
