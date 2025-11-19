 #include <stdio.h>
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[20], arrival[20], burst[20];
    int completion[20], turnaround[20], waiting[20];
    int done[20] = {0}; // track if process is completed
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    while (completed != n) {
        int idx = -1;
        int minBurst = 999999; // large number

        // Find process with shortest burst among those that have arrived
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && !done[i] && burst[i] < minBurst) {
                minBurst = burst[i];
                idx = i;
            }
        }

        if (idx != -1) {
            time += burst[idx]; // run process fully (non-preemptive)
            completion[idx] = time;
            turnaround[idx] = completion[idx] - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
            totalWT += waiting[idx];
            totalTAT += turnaround[idx];
            done[idx] = 1;
            completed++;
        } else {
            time++; // CPU idle
        }
    }

    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               pid[i], arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}