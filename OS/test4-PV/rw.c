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
	semid = semget(IPC_PRIVATE, 7 * sizeof(int), 0666|IPC_CREAT);
	shmid = shmget(IPC_PRIVATE, 11 * sizeof(int), 0666|IPC_CREAT);
	getid = shmget(IPC_PRIVATE, sizeof(int), 0666|IPC_CREAT);
	viraddr = (int*)shmat(shmid, 0, 0);
	get = (int*)shmat(getid, 0, 0);
	*get = 0;

	P.sem_flg = SEM_UNDO;
	P.sem_op = -1;
	V.sem_flg = SEM_UNDO;
	V.sem_op = 1;

	int v[] = {10, 0, 1, 0, 0, 1, 1};
	for (int i = 0; i < 7; ++i)
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
	for (int i = 0; i < 10; ++i)
	{
		p(0);

		viraddr[(*get)++] = i;

		v(1);
		sleep(1);
	}
}

void Read1()
{
	for (int i = 0; i < 5; ++i)
	{
		p(2);
		p(1);
		p(5);

		viraddr[10] = viraddr[--(*get)];

		v(5);
		v(0);
		v(3);
		sleep(1);
	}
}

void Read2()
{
	for (int i = 0; i < 5; ++i)
	{
		p(3);
		p(1);
		p(5);

		viraddr[10] = viraddr[10] * 10 + viraddr[--(*get)];

		v(5);
		v(0);
		v(4);
		sleep(1);
	}
}

void Parent()
{
	for (int i = 0; i < 5; ++i)
	{
		p(4);
		p(5);

		printf("%d\n", viraddr[10]);

		v(5);
		v(2);
		sleep(1);
	}
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
				sleep(1);
				shmdt(viraddr);
				shmctl(shmid, IPC_RMID, 0);
				semctl(semid, IPC_RMID, 0);
				semctl(getid, IPC_RMID, 0);
				exit(0);
			}
		}
	}
}
