#include <stdio.h>
#include "scheduler.h"


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