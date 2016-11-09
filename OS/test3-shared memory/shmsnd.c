#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//#include <linux/shm.h>

const int SHM = 233;

int main()
{
	int shmid;
	char *viraddr = NULL;
	while ((shmid = shmget(SHM, 1000, 0666|IPC_CREAT)) == -1);
	viraddr = (char*) shmat(shmid, 0, 0);

	for (int i = 0; i < 5; ++i)
	{
		char s[2];
		s[0] = i + '0';
		s[1] = '\0';
		strcat(viraddr, s);
	}
	strcat(viraddr, "end");

	shmdt(viraddr);
	return 0;
}
