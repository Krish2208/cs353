#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

int n = 100;
int numbers[100];
int result[NUM_THREADS] = {0};

void *sum_thread(void *arg) {
    int id = *(int*)arg;
    int start = id * n / NUM_THREADS;
    int end = (id + 1) * n / NUM_THREADS;
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += numbers[i];
    }
    result[id] = sum;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    for (int i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_thread, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        total_sum += result[i];
    }
    printf("The summation of the numbers is: %d\n", total_sum);
    return 0;
}