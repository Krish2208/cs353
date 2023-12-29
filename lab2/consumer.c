#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define SHMSIZE 27

int main() {
	char *s, *shm;
	key_t key = 5670;
	int shmid = shmget(key, SHMSIZE, 0666);
	shm = (char*) shmat(shmid, NULL, 0);

	for(s = shm; *s!=0; s++) putchar(*s);
	putchar('\n');

	*shm = '*';
	shmdt(s);
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}
