#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n = 10;
int arr[10], result[10];

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

void *quickSortHelper(void *arg) {
    int id = *(int*)arg;
    int low = id * 5;
    int high = low + 4;
    quickSort(arr, low, high);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[2];
    int thread_ids[2];

    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < 2; i++){
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, quickSortHelper, &thread_ids[i]);
    }
    for (int i = 0; i < 2; i++){
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    int i = 0, j = 5, k = 0;
    while (i < 5 && j < 10){
        if (arr[i] < arr[j]){
            result[k++] = arr[i++];
        }
        else{
            result[k++] = arr[j++];
        }
    }
    while (i < 5){
        result[k++] = arr[i++];
    }
    while (j < 10){
        result[k++] = arr[j++];
    }
    printf("\n");
    for (int i = 0; i < 10; i++){
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}