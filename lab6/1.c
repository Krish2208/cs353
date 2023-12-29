#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

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

    // Fork child processes
    pid_t pid_A, pid_B;
    pid_A = fork();
    if (pid_A == 0)
    {
        // Child process A
        for (int i = 0; i < 100000; i++)
        {
            (*shared_X)++;
            if (i % 10000)
                sleep(100 / 1000);
        }
        exit(0);
    }
    else
    {
        pid_B = fork();
        if (pid_B == 0)
        {
            // Child process B
            for (int i = 0; i < 100000; i++)
            {
                (*shared_X)--;
                if (i % 10000)
                    sleep(100 / 1000);
            }
            exit(0);
        }
        else
        {
            // Parent process
            waitpid(pid_A, NULL, 0);
            waitpid(pid_B, NULL, 0);
            printf("Final value of X: %d\n", *shared_X);

            // Detach and remove shared memory segment
            shmdt(shared_X);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }

    return 0;
}
