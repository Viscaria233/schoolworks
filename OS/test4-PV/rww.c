#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

int semid;
int shmid;
int getid;
struct sembuf P, V;
union semun arg;

int *viraddr = NULL;
int *get = NULL;

void init()
{
	int v[] = {10, 0, 1, 1, 0};
	int i;
	semid = semget(IPC_PRIVATE, 5 * sizeof(int), 0666|IPC_CREAT);
	shmid = shmget(IPC_PRIVATE, 12 * sizeof(int), 0666|IPC_CREAT);
	getid = shmget(IPC_PRIVATE, sizeof(int), 0666|IPC_CREAT);
	viraddr = (int*)shmat(shmid, 0, 0);
	get = (int*)shmat(getid, 0, 0);
	*get = 0;

	P.sem_flg = SEM_UNDO;
	P.sem_op = -1;
	V.sem_flg = SEM_UNDO;
	V.sem_op = 1;

	for (i = 0; i < 5; ++i)
	{
		arg.val = v[i];
		semctl(semid, i, SETVAL, arg);
	}
}

void p(int i)
{
	P.sem_num = i;
	semop(semid, &P, 1);
}

void v(int i)
{
	V.sem_num = i;
	semop(semid, &V, 1);
}

void Write()
{
	int i;
	for (i = 0; i < 10; ++i)
	{
		p(0);
		p(2);

		viraddr[(*get)++] = i;

		v(2);
		v(1);
		sleep(1);
	}
}

void Read1()
{
	int i;
	for (i = 0; i < 5; ++i)
	{
		p(3);
		p(1);
		p(2);

		printf("Read1: %d\n", viraddr[--(*get)]);
		viraddr[10] += viraddr[*get];

		v(2);
		v(0);
		v(4);
	}
}

void Read2()
{
	int i;
	for (i = 0; i < 5; ++i)
	{
		p(4);
		p(1);
		p(2);

		printf("Read2: %d\n", viraddr[--(*get)]);
		viraddr[11] += viraddr[*get];

		v(2);
		v(0);
		v(3);
	}
}

void Parent()
{
	wait(0);
	wait(0);
	wait(0);
	printf("sum1: %d, sum2: %d\n", viraddr[10], viraddr[11]);
	shmdt(viraddr);
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, IPC_RMID, 0);
	semctl(getid, IPC_RMID, 0);
}

int main()
{
	int chld[3];
	init();
	while ((chld[0] = fork()) == -1);
	if (chld[0] == 0)
	{
		Write();
		exit(0);
	}
	else
	{
		while ((chld[0] = fork()) == -1);
		if (chld[0] == 0)
		{
			Read1();
			exit(0);
		}
		else
		{
			while ((chld[0] = fork()) == -1);
			if (chld[0] == 0)
			{
				Read2();
				exit(0);
			}
			else
			{
				Parent();
				exit(0);
			}
		}
	}
}

