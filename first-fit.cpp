// First Fit Memory Allocation

#include <stdio.h>

int main() {
    int i, j, nb, np;

    printf("Enter number of blocks: ");
    scanf("%d", &nb);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int block[nb], process[np], allocation[np];

    printf("Enter block sizes:\n");
    for (i = 0; i < nb; i++) {
        scanf("%d", &block[i]);
    }

    printf("Enter process sizes:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &process[i]);
        allocation[i] = -1; // Not allocated
    }

    // First Fit Algorithm
    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (block[j] >= process[i]) {
                allocation[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, process[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}