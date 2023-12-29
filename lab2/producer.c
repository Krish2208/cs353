#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define SHMSIZE 27

int main(){
	char c;
	char *s, *shm;
	key_t key = 5670;
	int shmid = shmget(key, SHMSIZE, 0666|IPC_CREAT);
	shm = (char*) shmat(shmid, NULL, 0);

	s = shm;
	for(c = 'a'; c<='z'; c++) *s++ = c;
	*s = 0;

	while(*shm!='*') sleep(1);

	shmdt(s);
	shmctl(shmid, IPC_RMID, NULL);

	exit(0);
}
