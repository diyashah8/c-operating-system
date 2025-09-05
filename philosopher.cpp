#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
sem_t chopsticks[NUM_PHILOSOPHERS]; // One semaphore for each chopstick
pthread_t philosophers[NUM_PHILOSOPHERS];
int ids[NUM_PHILOSOPHERS];
// Function prototype for the philosopher thread
void* philosopher(void* arg);
int main() {
    // Initialize semaphores for each chopstick
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
        ids[i] = i;
    }
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    // Join all philosopher threads (they will run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    // Clean up semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }
    return 0;
}
void* philosopher(void* arg) {
    int id = *((int*)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;
    while (1) {
        // 1. Philosopher is thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);
        // 2. Philosopher tries to pick up chopsticks
        // To prevent deadlock, each philosopher first picks up the chopstick with the lower index.
        // The last philosopher picks up the one with the higher index first. This breaks the circular dependency.
        if (id == NUM_PHILOSOPHERS - 1) {
            // Last philosopher picks up the right chopstick first
            sem_wait(&chopsticks[right_chopstick]);
            printf("Philosopher %d picked up chopstick %d (right).\n", id, right_chopstick);
            sem_wait(&chopsticks[left_chopstick]);
            printf("Philosopher %d picked up chopstick %d (left).\n", id, left_chopstick);
        } else {
            // All other philosophers pick up the left chopstick first
            sem_wait(&chopsticks[left_chopstick]);
            printf("Philosopher %d picked up chopstick %d (left).\n", id, left_chopstick);
            sem_wait(&chopsticks[right_chopstick]);
            printf("Philosopher %d picked up chopstick %d (right).\n", id, right_chopstick);
        }

        // 3. Philosopher is eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // 4. Philosopher puts down chopsticks
        // They put them down in the reverse order to which they picked them up.
        sem_post(&chopsticks[right_chopstick]);
        printf("Philosopher %d put down chopstick %d (right).\n", id, right_chopstick);
        sem_post(&chopsticks[left_chopstick]);
        printf("Philosopher %d put down chopstick %d (left).\n", id, left_chopstick);
    }

    return NULL;
}
