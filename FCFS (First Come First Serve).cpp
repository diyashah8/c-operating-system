#include<stdio.h>
int main() {
    int n, i, j;
    int burst_time[20], arrival_time[20], completion_time[20];
    int waiting_time[20], turnaround_time[20];
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    printf("Enter the number of processes (max 20): ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process[%d] Arrival Time: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Process[%d] Burst Time: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    // Sort by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                // Swap arrival time
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;
                // Swap burst time
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
            }
        }
    }
    // Calculate Completion Time, Waiting Time, Turnaround Time
    int time = 0;
    for (i = 0; i < n; i++) {
        if (time < arrival_time[i])
            time = arrival_time[i];
        completion_time[i] = time + burst_time[i];
        waiting_time[i] = time - arrival_time[i];
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        time = completion_time[i];
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    // Display Results
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\n", i + 1, arrival_time[i], burst_time[i],
               completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time / n);
    return 0;
}
