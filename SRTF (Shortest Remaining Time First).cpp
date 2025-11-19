 #include <stdio.h>
#include <limits.h>

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int remaining;  // Remaining Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed != n) {
        int idx = -1;
        int minRemaining = INT_MAX;//2147483647

        // Find process with shortest remaining time at current time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minRemaining) {
                minRemaining = p[i].remaining;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].remaining--;
            time++;

            if (p[idx].remaining == 0) {
                completed++;
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                totalWT += p[idx].waiting;
                totalTAT += p[idx].turnaround;
            }
        } else {
            time++; // No process available, idle CPU
        }
    }

    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}

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