#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

const int SHM = 233;

void func(int);
int k;

void func(int sig)
{
	k = 0;
}

int main()
{
	int shmid;
	char *viraddr = NULL;
	int frk;
	while ((shmid = shmget(SHM, 1000, 0666 | IPC_CREAT)) == -1);
	viraddr = (char*) shmat(shmid, 0, 0);

	signal(SIGUSR1, func);
	k = 1;

	while ((frk = fork()) == -1);
	if (frk == 0)
	{
		while (k == 1);
		*strstr(viraddr, "end") = '\0';
		printf("%s\n", viraddr);
		shmdt(viraddr);
		shmctl(shmid, IPC_RMID, 0);
		exit(0);
	}
	else
	{
		for (int i = 0; i < 5; ++i)
		{
		    char s[2];
			s[0] = i + 'A';
			s[1] = '\0';
			strcat(viraddr, s);
		}
		strcat(viraddr, "end");
		shmdt(viraddr);
		kill(frk, SIGUSR1);
		exit(0);
	}

	return 0;
}
