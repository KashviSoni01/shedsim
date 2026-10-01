#include <stdio.h>
#include "process.h"


// Sort processes according to arrival time
void sortByArrival(Process processes[], int n) {

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n - 1; j++) {

            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {

                Process temp = processes[j];

                processes[j] = processes[j + 1];

                processes[j + 1] = temp;
            }
        }
    }
}


// FCFS Scheduling
void fcfs(Process processes[], int n) {

    int currentTime = 0;

    for (int i = 0; i < n; i++) {

        //CPU is idle, move time forward
        if(currentTime < processes[i].arrivalTime) {
            currentTime=processes[i].arrivalTime;
        }
        
        //time when process first starts
        processes[i].startTime = currentTime;


        // Run the process
        currentTime += processes[i].burstTime;


        // Completion Time
        processes[i].completionTime = currentTime;

        // Turnaround Time
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;


        // Waiting Time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;


        // Response Time
        processes[i].responseTime = processes[i].startTime - processes[i].arrivalTime;
    }
}

// Print FCFS Gantt Chart
// Print FCFS Gantt Chart
void printGanttChart(Process processes[], int n) {

    printf("\n\nGantt Chart\n\n");

    int previousFinish = 0;

    // -------------------------------
    // TOP BORDER
    // -------------------------------

    for (int i = 0; i < n; i++) {

        // Print IDLE block if there is a gap
        if (processes[i].startTime > previousFinish) {
            printf("+--------");
        }

        printf("+--------");
    }

    printf("+\n");


    // -------------------------------
    // PROCESS / IDLE LABELS
    // -------------------------------

    previousFinish = 0;

    printf("|");

    for (int i = 0; i < n; i++) {

        // CPU was idle before this process
        if (processes[i].startTime > previousFinish) {

            printf("  IDLE  |");
        }

        // Process block
        printf("   P%d   |", processes[i].pid);

        previousFinish = processes[i].completionTime;
    }

    printf("\n");


    // -------------------------------
    // BOTTOM BORDER
    // -------------------------------

    previousFinish = 0;

    for (int i = 0; i < n; i++) {

        if (processes[i].startTime > previousFinish) {
            printf("+--------");
        }

        printf("+--------");
    }

    printf("+\n");


    // -------------------------------
    // TIMESTAMPS
    // -------------------------------

    previousFinish = 0;

    printf("%-8d", 0);

    for (int i = 0; i < n; i++) {

        // Print the arrival/start time of an idle gap
        if (processes[i].startTime > previousFinish) {
            printf("%-8d", processes[i].startTime);
        }

        printf("%-8d", processes[i].completionTime);

        previousFinish = processes[i].completionTime;
    }

    printf("\n");
}

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