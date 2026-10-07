
#include <stdio.h>
#include "process.h"
#include "scheduler.h"

int main()
{
    int n;
    int choice;
    int quantum = 0;

    Process processes[100];
    ScheduleSegment segments[10000];
    int segmentCount = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid number of processes. Enter 1 to 100.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);

        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);

        printf("Priority: ");
        scanf("%d", &processes[i].priority);

        if (processes[i].arrivalTime < 0 ||
            processes[i].burstTime <= 0)
        {
            printf("Arrival time must be non-negative and burst time must be positive.\n");
            return 1;
        }

        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF (Non-Preemptive)\n");
    printf("3. Priority Scheduling (Non-Preemptive)\n");
    printf("4. SRTF (Preemptive)\n");
    printf("5. Round Robin\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        fcfs(processes, n);
        printGanttChart(processes, n);
    }
    else if (choice == 2)
    {
        sjf(processes, n);
        printGanttChart(processes, n);
    }
    else if (choice == 3)
    {
        priorityScheduling(processes, n);
        printGanttChart(processes, n);
    }
 else if (choice == 4)
{
    segmentCount = srtf(processes, n, segments);

    printSegmentGanttChart(segments, segmentCount);
}
    else if (choice == 5)
    {
        printf("Enter time quantum: ");
        scanf("%d", &quantum);

        if (quantum <= 0)
        {
            printf("Time quantum must be greater than zero.\n");
            return 1;
        }

        segmentCount = roundRobin(
            processes,
            n,
            quantum,
            segments);

        printSegmentGanttChart(segments, segmentCount);
    }

    else
    {
        printf("Invalid scheduling algorithm choice.\n");
        return 1;
    }

    double totalWaiting = 0;
    double totalTurnaround = 0;
    double totalResponse = 0;

    for (int i = 0; i < n; i++)
    {
        totalWaiting += processes[i].waitingTime;
        totalTurnaround += processes[i].turnaroundTime;
        totalResponse += processes[i].responseTime;
    }

    double averageWaiting = totalWaiting / n;
    double averageTurnaround = totalTurnaround / n;
    double averageResponse = totalResponse / n;

    printf("\n");
    printf("--------------------------------------------------------------------------\n");
    printf("PID   Arrival   Burst   Completion   Turnaround   Waiting   Response\n");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%-5d %-9d %-7d %-12d %-12d %-9d %d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime,
               processes[i].responseTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", averageWaiting);
    printf("Average Turnaround Time: %.2f\n", averageTurnaround);
    printf("Average Response Time: %.2f\n", averageResponse);

    return 0;
}