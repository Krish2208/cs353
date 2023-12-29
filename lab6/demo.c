#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>

int P(int semid, int semnum) {
    // Operation taking resource and no flag
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op = -1;
    sb.sem_flg = 0;
    return semop(semid, &sb, 1);
}

int V(int semid, int semnum) {
    // Operation releasing resource and no flag
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op = 1;
    sb.sem_flg = 0;
    return semop(semid, &sb, 1);
}

int main() {
    int semID1, semID2, flag, count = 10, data = 0;
    char* str;
    FILE *fp;
    
    semID1 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
    semID2 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);

    semctl(semID1, 0, SETVAL, 0);
    semctl(semID2, 0, SETVAL, 1);

    if(fork() == 0){
        while(count){
            P(semID1, 0);
            fp = fopen("./datafile", "r");
            fscanf(fp, "%d", &data);
            printf("\t\t\t\t Consumer Reads: %d\n", data);
            fclose(fp);
            V(semID2, 0);
            count--;
        }
    }
    else{
        while(count){
            sleep(1);
            P(semID2, 0);
            fp = fopen("./datafile", "w");
            fprintf(fp, "%d", data);
            printf("Producer Writes: %d\n", data);
            data++;
            fclose(fp);
            V(semID1, 0);
            count--;
        }
    }

    semctl(semID1, 0, IPC_RMID, 0);
    semctl(semID2, 0, IPC_RMID, 0);
    return 0;
}