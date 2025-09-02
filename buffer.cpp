#include <stdio.h>
#include <stdlib.h>
// Define the buffer size
#define BUFFER_SIZE 5
// Global variables for the buffer, pointers, and item count
int buffer[BUFFER_SIZE];
int in = 0;   // Producer's pointer (index to add to)
int out = 0;  // Consumer's pointer (index to consume from)
int count = 0; // Number of items currently in the buffer
// Function prototypes
void produce();
void consume();
void display_buffer();
int main() {
    int choice = 0;
    while (choice != 4) {
        printf("\n\n-- Producer-Consumer Bounded Buffer --");
        printf("\n1. Produce an item");
        printf("\n2. Consume an item");
        printf("\n3. Display buffer status");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
		 {
            case 1:
                produce();
                break;
            case 2:
                consume();
                break;
            case 3:
                display_buffer();
                break;
            case 4:
                printf("\nExiting program.\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    return 0;
}
// Function to add an item to the buffer (producer)
void produce() {
    if (count == BUFFER_SIZE) {
        printf("\nBuffer is full! Cannot produce.\n");
    } else {
        int item;
        printf("Enter the item to produce: ");
        scanf("%d", &item);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Produced item: %d\n", item);
    }
}
// Function to remove an item from the buffer (consumer)
void consume() {
    if (count == 0) {
        printf("\nBuffer is empty! Cannot consume.\n");
    } else {
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumed item: %d\n", item);
    }
}
// Function to display the current state of the buffer
void display_buffer() {
    printf("\n-- Buffer Status --\n");
    if (count == 0) {
        printf("Buffer is empty.\n");
    } else {
        printf("Items in buffer: %d\n", count);
        printf("Contents: ");
        int i, j;
        for (i = 0, j = out; i < count; i++) {
            printf("%d ", buffer[j]);
            j = (j + 1) % BUFFER_SIZE;
        }
        printf("\n");
        printf("in index: %d, out index: %d\n", in, out);
    }
}
