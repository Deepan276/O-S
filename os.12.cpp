#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        usleep(rand() % 1000000); 

        printf("Philosopher %d is hungry\n", id);

        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d picked up fork %d (left)\n", id, left_fork);
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up fork %d (right)\n", id, right_fork);

        printf("Philosopher %d is eating\n", id);
        usleep(rand() % 1000000); 
        pthread_mutex_unlock(&forks[right_fork]);
        printf("Philosopher %d put down fork %d (right)\n", id, right_fork);
        pthread_mutex_unlock(&forks[left_fork]);
        printf("Philosopher %d put down fork %d (left)\n", id, left_fork);
    }
}

int main() {
    srand(time(NULL));

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

