#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define SHM_SIZE 10 * sizeof(int)

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int j;
    for (j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int shmid, *shm_ptr;
    pid_t pid1, pid2;
    int arr[10];
    int arr1[5], arr2[5];
    int i;
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    shm_ptr = shmat(shmid, NULL, 0);
    printf("Enter 10 integers to be sorted:\n");
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &shm_ptr[i]);
    }
    pid1 = fork();
    if (pid1 != 0)
        pid2 = fork();
    if (pid1 == 0 || pid2 == 0)
    {
        for (i = 0; i < 5; i++)
        {
            arr1[i] = shm_ptr[i];
            arr2[i] = shm_ptr[i + 5];
        }
        if (pid1 == 0)
        {
            quickSort(arr1, 0, 4);
            printf("Child process sorted the first half of the integers using quick sort:\n");
            for (i = 0; i < 5; i++)
            {
                printf("%d ", arr1[i]);
            }
            printf("\n");
            for (i = 0; i < 5; i++)
            {
                shm_ptr[i] = arr1[i];
            }
        }
        else
        {
            quickSort(arr2, 0, 4);
            printf("Child process sorted the second half of the integers using quick sort:\n");
            for (i = 0; i < 5; i++)
            {
                printf("%d ", arr2[i]);
            }
            printf("\n");
            for (i = 0; i < 5; i++)
            {
                shm_ptr[i + 5] = arr2[i];
            }
        }
    }
    else
    {
        wait(NULL);
        printf("Parent process sorted the integers using merge sort:\n");
        int i = 0, j = 0;
        for (i = 0; i < 5; i++)
        {
            arr1[i] = shm_ptr[i];
            arr2[i] = shm_ptr[i + 5];
        }
        i = 0, j = 0;
        while (i < 5 && j < 5)
        {
            if (arr1[i] < arr2[j])
            {
                arr[i + j] = arr1[i];
                i++;
            }
            else
            {
                arr[i + j] = arr2[j];
                j++;
            }
        }
        while (i < 5)
        {
            arr[i + j] = arr1[i];
            i++;
        }
        while (j < 5)
        {
            arr[i + j] = arr2[j];
            j++;
        }
        for (i = 0; i < 10; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}