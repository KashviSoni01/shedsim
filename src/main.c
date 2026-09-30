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
        int startTime = currentTime;


        // Run the process
        currentTime += processes[i].burstTime;


        // Completion Time
        processes[i].completionTime = currentTime;

        // Turnaround Time
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;


        // Waiting Time
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;


        // Response Time
        processes[i].responseTime = startTime - processes[i].arrivalTime;
    }
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


    return 0;
}