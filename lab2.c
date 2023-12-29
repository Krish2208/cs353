#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    sem_t *empty;
    sem_t *full;
    sem_t *mutex;
    int in;
    int out;
} shared_data;

int main() {
    int shm_fd = shm_open("/buffer", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));
    shared_data *data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    data->empty = sem_open("/empty", O_CREAT | O_RDWR, 0666, BUFFER_SIZE);
    data->full = sem_open("/full", O_CREAT | O_RDWR, 0666, 0);
    data->mutex = sem_open("/mutex", O_CREAT | O_RDWR, 0666, 1);
    data->in = 0;
    data->out = 0;

    pid_t pid = fork();
    if (pid == 0) {
        // Producer process
        int item = 0;
        while (1) {
            sem_wait(data->empty);
            sem_wait(data->mutex);

            data->buffer[data->in] = item;
            printf("Produced item %d\n", item);
            item++;
            data->in = (data->in + 1) % BUFFER_SIZE;

            sem_post(data->mutex);
            sem_post(data->full);

            sleep(1);
        }
    } else if (pid > 0) {
        // Consumer process
        while (1) {
            sem_wait(data->full);
            sem_wait(data->mutex);

            int item = data->buffer[data->out];
            printf("Consumed item %d\n", item);
            data->out = (data->out + 1) % BUFFER_SIZE;

            sem_post(data->mutex);
            sem_post(data->empty);

            sleep(2);
        }
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
