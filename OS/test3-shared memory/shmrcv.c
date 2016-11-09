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

	*strstr(viraddr, "end") = '\0';

	printf("%s\n", viraddr);

	shmdt(viraddr);
	shmctl(shmid, IPC_RMID, 0);
	return 0;
}
