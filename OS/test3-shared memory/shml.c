#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>
#include <signal.h>

const int ARRAY_LEN = 30;

void func1(int);
void func2(int);
int s1, s2;

void func1(int sig)
{
	s1 = 0;
}

void func2(int sig)
{
	s2 = 0;
}

int main()
{
	int shmid;
	int *array = NULL;
	int chid1, chid2, i;

	shmid = shmget(233, ARRAY_LEN * sizeof(int), 0666 | IPC_CREAT);
	array = shmat(shmid, 0, 0);

	s1 = 1;
	s2 = 1;
	signal(SIGUSR1, func1);
	signal(SIGUSR2, func2);

	while ((chid1 = fork()) == -1);
	if (chid1 == 0)
	{
		while (s2 == 1);
		for (i = 0; i < 20; ++i)
		{
			printf("get: %d\n", array[i]);
		}
		kill(chid1, SIGUSR1);
		exit(0);
	}
	else
	{
		while ((chid2 = fork()) == -1);
		if (chid2 == 0)
		{
			for (i = 0; i < 20; ++i)
			{
				int n = pow(2, i);
				array[i] = n;
				printf("send: %d\n", n);
			}
			kill(chid2, SIGUSR2);
			exit(0);
		}
		else
		{
			while (s1 == 1 || s2 == 1);
			shmdt(array);
			shmctl(shmid, IPC_RMID, 0);
			exit(0);
		}
	}
	return 0;
}
