#include <stdio.h>
#define SIZE 10
int buffer[SIZE];
int in = 0, out = 0;
int mutex = 1;        // Binary semaphore for mutual exclusion
int full = 0;         // Counts filled slots
int empty = SIZE;     // Counts empty slots

// Semaphore operations
int wait(int s) {
    return --s;
}

int signal(int s) {
    return ++s;
}

int main() {
    int choice, item;
    while(1) {
        printf("\n1. Produce\t2. Consume\t3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // Produce
                if (empty == 0)
                    printf("\nBuffer is Full!");
                else if (mutex == 1) {
                    mutex = wait(mutex);
                    empty = wait(empty);
                    printf("Enter the item to produce: ");
                    scanf("%d", &item);
                    buffer[in] = item;
                    in = (in + 1) % SIZE;
                    full = signal(full);
                    mutex = signal(mutex);
                }
                break;
            case 2: // Consume
                if (full == 0)
                    printf("\nBuffer is Empty!");
                else if (mutex == 1) {
                    mutex = wait(mutex);
                    full = wait(full);
                    item = buffer[out];
                    printf("Consumed item: %d", item);
                    out = (out + 1) % SIZE;
                    empty = signal(empty);
                    mutex = signal(mutex);
                }
                break;
            case 3:
                return 0;
            default:
                printf("\nInvalid choice!");
        }
    }
}

