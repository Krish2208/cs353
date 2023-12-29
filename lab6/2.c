#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/sem.h>

#define SHM_SIZE sizeof(int)

int main()
{
    int X;
    printf("Enter a value for X: ");
    scanf("%d", &X);

    // Create shared memory segment
    key_t key = ftok(".", 'X');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    // Attach shared memory segment to pointer
    int *shared_X = (int *)shmat(shmid, NULL, 0);

    // Initialize shared memory variable
    *shared_X = X;

    // Create semaphore
    int semid = semget(key, 1, IPC_CREAT | 0666);
    struct sembuf sb;

    semctl(semid, 0, SETVAL, 1);

    // Fork child process
    pid_t pid_A = fork();

    if (pid_A == 0)
    {
        // Child process
        // Wait for semaphore
        struct sembuf sem_buf;
        sem_buf.sem_num = 0;
        sem_buf.sem_op = -1;
        sem_buf.sem_flg = 0;
        semop(semid, &sem_buf, 1);

        // Read shared memory variable
        int X = *shared_X;

        // Perform calculation
        for (int i = 0; i < 100000; i++) X++;

        // Write result to shared memory variable
        *shared_X = X;

        // Release semaphore
        sem_buf.sem_op = 1;
        semop(semid, &sem_buf, 1);

        exit(0);
    }
    else
    {
        pid_t pid_B = fork();

        if (pid_B == 0)
        {
            // Child process
            // Wait for semaphore
            struct sembuf sem_buf;
            sem_buf.sem_num = 0;
            sem_buf.sem_op = -1;
            sem_buf.sem_flg = 0;
            semop(semid, &sem_buf, 1);

            // Read shared memory variable
            int X = *shared_X;

            // Perform calculation
            for (int i = 0; i < 100000; i++) X--;

            // Write result to shared memory variable
            *shared_X = X;

            // Release semaphore
            sem_buf.sem_op = 1;
            semop(semid, &sem_buf, 1);

            exit(0);
        }
        else
        {
            waitpid(pid_A, NULL, 0);
            waitpid(pid_B, NULL, 0);
            printf("Final value of X: %d\n", *shared_X);
            
            // Detach and remove shared memory segment
            shmdt(shared_X);
            shmctl(shmid, IPC_RMID, NULL);

            // Remove semaphore
            semctl(semid, 0, IPC_RMID, 0);
        }
    }

    return 0;
}