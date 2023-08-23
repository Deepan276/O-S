#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < 10000; i++) {
        counter++;
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Counter value: %d\n", counter);

    return 0;
}
