#include <stdio.h>
#include "process.h"

int main() {

    int n;
    Process processes[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        processes[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);

        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);

        printf("Priority: ");
        scanf("%d", &processes[i].priority);

        // Initially, remaining time is the same as burst time
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\n--------------------------------\n");
    printf("PID   Arrival   Burst   Priority\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d      %d        %d        %d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority);
    }

    return 0;
}