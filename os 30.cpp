#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d is running.\n", thread_id);
    sleep(2);
    printf("Thread %d is done.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    // Creating threads
    pthread_create(&thread1, NULL, thread_function, &id1);
    pthread_create(&thread2, NULL, thread_function, &id2);

    // Joining threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads are done.\n");

    return 0;
}
