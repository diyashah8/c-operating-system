#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declare global synchronization variables
sem_t mutex, wrt;
int read_count = 0;

// Function prototypes
void* reader(void* arg);
void* writer(void* arg);

int main() {
    pthread_t r[5], w[5];
    int ids[5];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader and writer threads
    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &ids[i]);
        pthread_create(&w[i], NULL, writer, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

// Reader thread function
void* reader(void* arg) {
    int id = *((int*)arg);

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt); // First reader locks writers
    sem_post(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1); // Simulate reading

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt); // Last reader unlocks writers
    sem_post(&mutex);

    return NULL;
}

// Writer thread function
void* writer(void* arg) {
    int id = *((int*)arg);

    sem_wait(&wrt); // Writer locks access
    printf("Writer %d is writing\n", id);
    sleep(2); // Simulate writing
    sem_post(&wrt); // Writer unlocks access

    return NULL;
}

