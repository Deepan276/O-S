#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0;
int readers_count = 0;
sem_t mutex, rw_mutex;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        printf("Reader %d read data: %d\n", *(int *)arg, data);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&rw_mutex);

        data = *(int *)arg;
        printf("Writer wrote data: %d\n", data);

        sem_post(&rw_mutex);
    }
}

int main() {
    pthread_t readers[NUM_READERS],
