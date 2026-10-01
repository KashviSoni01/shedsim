#include <stdio.h>
#include "process.h"
#include "scheduler.h"




int main() {

    int n;
    Process processes[100];


    // -------------------------------
    // INPUT
    // -------------------------------

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

        // Initially remaining time = burst time
        processes[i].remainingTime = processes[i].burstTime;
    }

    sortByArrival(processes, n);
    fcfs(processes, n);
    printGanttChart(processes, n);

    // CALCULATE AVERAGES

    double totalWaiting = 0;
    double totalTurnaround = 0;
    double totalResponse = 0;

    for (int i = 0; i < n; i++) {

        totalWaiting += processes[i].waitingTime;

        totalTurnaround += processes[i].turnaroundTime;

        totalResponse += processes[i].responseTime;
    }

    double averageWaiting = totalWaiting / n;

    double averageTurnaround = totalTurnaround / n;

    double averageResponse = totalResponse / n;

    //Display Result
    printf("\n");
    printf("-------------------------------------------------------------\n");

    printf("PID   Arrival   Burst   Completion   Turnaround   Waiting   Response\n");

    printf("-------------------------------------------------------------\n");


    for (int i = 0; i < n; i++) {

        printf("P%d      %d        %d        %d           %d          %d         %d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime,
               processes[i].responseTime);
    }

    // Display averages
    printf("\nAverage Waiting Time: %.2f\n", averageWaiting);
    printf("Average Turnaround Time: %.2f\n", averageTurnaround);
    printf("Average Response Time: %.2f\n", averageResponse);

    return 0;
}