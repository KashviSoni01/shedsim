#include <stdio.h>
#include "scheduler.h"

// Sort processes according to arrival time
void sortByArrival(Process processes[], int n)
{

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n - 1; j++)
        {

            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {

                Process temp = processes[j];

                processes[j] = processes[j + 1];

                processes[j + 1] = temp;
            }
        }
    }
}

// FCFS Scheduling
void fcfs(Process processes[], int n)
{

    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {

        // CPU is idle, move time forward
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        // time when process first starts
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

// SJF Scheduling
void sjf(Process processes[], int n)
{

    sortByArrival(processes, n);

    int currentTime = processes[0].arrivalTime;

    int completed[n];

    for (int i = 0; i < n; i++)
    {
        completed[i] = 0;
    }

    for (int count = 0; count < n; count++)
    {

        int shortestIndex = -1;

        // Find shortest process that has arrived
        for (int i = 0; i < n; i++)
        {

            if (completed[i] == 0 &&
                processes[i].arrivalTime <= currentTime)
            {

                if (shortestIndex == -1 ||
                    processes[i].burstTime <
                        processes[shortestIndex].burstTime)
                {

                    shortestIndex = i;
                }
            }
        }

        if (shortestIndex == -1)
        {

            currentTime = processes[count].arrivalTime;

            // Search again for the shortest available process
            for (int i = 0; i < n; i++)
            {

                if (completed[i] == 0 &&
                    processes[i].arrivalTime <= currentTime)
                {

                    if (shortestIndex == -1 ||
                        processes[i].burstTime <
                            processes[shortestIndex].burstTime)
                    {

                        shortestIndex = i;
                    }
                }
            }
        }

        // Run selected process
        processes[shortestIndex].startTime = currentTime;

        currentTime += processes[shortestIndex].burstTime;

        processes[shortestIndex].completionTime = currentTime;

        processes[shortestIndex].turnaroundTime =
            processes[shortestIndex].completionTime -
            processes[shortestIndex].arrivalTime;

        processes[shortestIndex].waitingTime =
            processes[shortestIndex].turnaroundTime -
            processes[shortestIndex].burstTime;

        processes[shortestIndex].responseTime =
            processes[shortestIndex].startTime -
            processes[shortestIndex].arrivalTime;

        completed[shortestIndex] = 1;
    }
}

// Shortest Remaning Time First Scheduling
int srtf(Process processes[], int n, ScheduleSegment segments[])
{
    for (int i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].started = 0;
    }

    int currentTime = 0;
    int completed = 0;
    int segmentCount = 0;

    int completedProcess[n];

    for (int i = 0; i < n; i++)
    {
        completedProcess[i] = 0;
    }

    int lastProcess = -1;
    int segmentStart = 0;

    while (completed < n)
    {
        int selected = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (completedProcess[i] == 0 &&
                processes[i].arrivalTime <= currentTime)
            {
                if (selected == -1 ||
                    processes[i].remainingTime < processes[selected].remainingTime)
                {
                    selected = i;
                }
            }
        }

        // CPU is idle
        if (selected == -1)
        {
            // Finish the previous segment if one exists
            if (lastProcess != -1)
            {
                segments[segmentCount].pid =
                    processes[lastProcess].pid;

                segments[segmentCount].startTime = segmentStart;
                segments[segmentCount].endTime = currentTime;

                segmentCount++;

                lastProcess = -1;
            }

            int nextArrival = -1;

            for (int i = 0; i < n; i++)
            {
                if (completedProcess[i] == 0)
                {
                    if (nextArrival == -1 ||
                        processes[i].arrivalTime <
                        processes[nextArrival].arrivalTime)
                    {
                        nextArrival = i;
                    }
                }
            }

            // Record idle period
            if (currentTime < processes[nextArrival].arrivalTime)
            {
                segments[segmentCount].pid = 0;
                segments[segmentCount].startTime = currentTime;
                segments[segmentCount].endTime =
                    processes[nextArrival].arrivalTime;

                segmentCount++;
            }

            currentTime = processes[nextArrival].arrivalTime;
            continue;
        }

        // A different process has been selected
        if (selected != lastProcess)
        {
            // Finish the previous process's segment
            if (lastProcess != -1)
            {
                segments[segmentCount].pid =
                    processes[lastProcess].pid;

                segments[segmentCount].startTime = segmentStart;
                segments[segmentCount].endTime = currentTime;

                segmentCount++;
            }

            // Start a new segment
            segmentStart = currentTime;
            lastProcess = selected;
        }

        // Record response time when process runs for the first time
        if (processes[selected].started == 0)
        {
            processes[selected].startTime = currentTime;

            processes[selected].responseTime =
                currentTime - processes[selected].arrivalTime;

            processes[selected].started = 1;
        }

        // Execute for one unit of time
        processes[selected].remainingTime--;
        currentTime++;

        // Process completed
        if (processes[selected].remainingTime == 0)
        {
            processes[selected].completionTime = currentTime;

            processes[selected].turnaroundTime =
                processes[selected].completionTime -
                processes[selected].arrivalTime;

            processes[selected].waitingTime =
                processes[selected].turnaroundTime -
                processes[selected].burstTime;

            completedProcess[selected] = 1;
            completed++;
        }
    }

    // Finish the final segment
    if (lastProcess != -1)
    {
        segments[segmentCount].pid =
            processes[lastProcess].pid;

        segments[segmentCount].startTime = segmentStart;
        segments[segmentCount].endTime = currentTime;

        segmentCount++;
    }

    return segmentCount;
}

// Round Robin Sheduling
int roundRobin(
    Process processes[],
    int n,
    int quantum,
    ScheduleSegment segments[])
{
    int queue[100];
    int front = 0;
    int rear = 0;
    int queueCount = 0;
    int segmentCount = 0;

    if (n <= 0 || n > 100 || quantum <= 0)
        return 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].started = 0;
    }

    sortByArrival(processes, n);

    int currentTime = 0;
    int completed = 0;
    int nextArrival = 0;

    while (nextArrival < n &&
           processes[nextArrival].arrivalTime <= currentTime)
    {
        queue[rear] = nextArrival;
        rear = (rear + 1) % 100;
        queueCount++;
        nextArrival++;
    }

    while (completed < n)
    {
        if (queueCount == 0)
        {
            int nextTime = processes[nextArrival].arrivalTime;

            // Record the CPU idle period
            segments[segmentCount].pid = 0;
            segments[segmentCount].startTime = currentTime;
            segments[segmentCount].endTime = nextTime;
            segmentCount++;

            currentTime = nextTime;

            while (nextArrival < n &&
                   processes[nextArrival].arrivalTime <= currentTime)
            {
                queue[rear] = nextArrival;
                rear = (rear + 1) % 100;
                queueCount++;
                nextArrival++;
            }
        }

        int processIndex = queue[front];
        front = (front + 1) % 100;
        queueCount--;

        int timeSlice;

        if (processes[processIndex].remainingTime < quantum)
            timeSlice = processes[processIndex].remainingTime;
        else
            timeSlice = quantum;

        if (processes[processIndex].started == 0)
        {
            processes[processIndex].startTime = currentTime;
            processes[processIndex].responseTime =
                currentTime - processes[processIndex].arrivalTime;

            processes[processIndex].started = 1;
        }

        // Record the start of this execution segment
        segments[segmentCount].pid = processes[processIndex].pid;
        segments[segmentCount].startTime = currentTime;

        currentTime += timeSlice;

        // Record the end of this execution segment
        segments[segmentCount].endTime = currentTime;
        segmentCount++;

        processes[processIndex].remainingTime -= timeSlice;

        while (nextArrival < n &&
               processes[nextArrival].arrivalTime <= currentTime)
        {
            queue[rear] = nextArrival;
            rear = (rear + 1) % 100;
            queueCount++;
            nextArrival++;
        }

        if (processes[processIndex].remainingTime == 0)
        {
            processes[processIndex].completionTime = currentTime;

            processes[processIndex].turnaroundTime =
                currentTime - processes[processIndex].arrivalTime;

            processes[processIndex].waitingTime =
                processes[processIndex].turnaroundTime -
                processes[processIndex].burstTime;

            completed++;
        }
        else
        {
            queue[rear] = processIndex;
            rear = (rear + 1) % 100;
            queueCount++;
        }
    }

    return segmentCount;
}

// Priority Scheduling
void priorityScheduling(Process processes[], int n)
{
    sortByArrival(processes, n);

    int currentTime = processes[0].arrivalTime;
    int completed = 0;

    int completedProcess[n];

    for (int i = 0; i < n; i++)
    {
        completedProcess[i] = 0;
    }

    while (completed < n)
    {
        int selected = -1;

        for (int i = 0; i < n; i++)
        {
            if (completedProcess[i] == 0 &&
                processes[i].arrivalTime <= currentTime)
            {
                if (selected == -1 ||
                    processes[i].priority < processes[selected].priority)
                {
                    selected = i;
                }
            }
        }

        if (selected == -1)
        {
            // CPU is idle.
            // Find the earliest arriving unfinished process.

            int nextArrival = -1;

            for (int i = 0; i < n; i++)
            {
                if (completedProcess[i] == 0)
                {
                    if (nextArrival == -1 ||
                        processes[i].arrivalTime < processes[nextArrival].arrivalTime)
                    {
                        nextArrival = i;
                    }
                }
            }

            currentTime = processes[nextArrival].arrivalTime;
        }
        else
        {
            processes[selected].startTime = currentTime;

            processes[selected].responseTime =
                currentTime - processes[selected].arrivalTime;

            currentTime += processes[selected].burstTime;

            processes[selected].completionTime = currentTime;

            processes[selected].turnaroundTime =
                processes[selected].completionTime -
                processes[selected].arrivalTime;

            processes[selected].waitingTime =
                processes[selected].turnaroundTime -
                processes[selected].burstTime;

            completedProcess[selected] = 1;
            completed++;
        }
    }
}

//Preemptive Priority Scheduling
int preemptivePriority(
    Process processes[],
    int n,
    ScheduleSegment segments[])
{
    for (int i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].started = 0;
    }

    int currentTime = 0;
    int completed = 0;
    int segmentCount = 0;

    int completedProcess[n];

    for (int i = 0; i < n; i++)
    {
        completedProcess[i] = 0;
    }

    int lastProcess = -1;
    int segmentStart = 0;

    while (completed < n)
    {
        int selected = -1;

        for (int i = 0; i < n; i++)
        {
            if (completedProcess[i] == 0 &&
                processes[i].arrivalTime <= currentTime)
            {
                if (selected == -1 ||
                    processes[i].priority < processes[selected].priority)
                {
                    selected = i;
                }
            }
        }


        if (selected == -1)
        {
            if (lastProcess != -1)
            {
                segments[segmentCount].pid =
                    processes[lastProcess].pid;

                segments[segmentCount].startTime = segmentStart;
                segments[segmentCount].endTime = currentTime;

                segmentCount++;

                lastProcess = -1;
            }

            int nextArrival = -1;

            for (int i = 0; i < n; i++)
            {
                if (completedProcess[i] == 0)
                {
                    if (nextArrival == -1 ||
                        processes[i].arrivalTime <
                        processes[nextArrival].arrivalTime)
                    {
                        nextArrival = i;
                    }
                }
            }

        
            if (currentTime < processes[nextArrival].arrivalTime)
            {
                segments[segmentCount].pid = 0;
                segments[segmentCount].startTime = currentTime;
                segments[segmentCount].endTime =
                    processes[nextArrival].arrivalTime;

                segmentCount++;
            }

            currentTime = processes[nextArrival].arrivalTime;
            continue;
        }


        if (selected != lastProcess)
        {
            if (lastProcess != -1)
            {
                segments[segmentCount].pid =
                    processes[lastProcess].pid;

                segments[segmentCount].startTime = segmentStart;
                segments[segmentCount].endTime = currentTime;

                segmentCount++;
            }

            segmentStart = currentTime;
            lastProcess = selected;
        }

        if (processes[selected].started == 0)
        {
            processes[selected].startTime = currentTime;

            processes[selected].responseTime =
                currentTime - processes[selected].arrivalTime;

            processes[selected].started = 1;
        }

        processes[selected].remainingTime--;
        currentTime++;

        if (processes[selected].remainingTime == 0)
        {
            processes[selected].completionTime = currentTime;

            processes[selected].turnaroundTime =
                processes[selected].completionTime -
                processes[selected].arrivalTime;

            processes[selected].waitingTime =
                processes[selected].turnaroundTime -
                processes[selected].burstTime;

            completedProcess[selected] = 1;
            completed++;
        }
    }

    if (lastProcess != -1)
    {
        segments[segmentCount].pid =
            processes[lastProcess].pid;

        segments[segmentCount].startTime = segmentStart;
        segments[segmentCount].endTime = currentTime;

        segmentCount++;
    }

    return segmentCount;
}

// Print Gantt Chart
void printGanttChart(Process processes[], int n)
{
    printf("\n\nGantt Chart\n\n");

    // Make a copy so we don't change the original process order
    Process order[n];

    for (int i = 0; i < n; i++)
    {
        order[i] = processes[i];
    }

    // Sort the copy by start time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (order[j].startTime > order[j + 1].startTime)
            {
                Process temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    int previousFinish = 0;

    // -------------------------------
    // TOP BORDER
    // -------------------------------

    for (int i = 0; i < n; i++)
    {
        // IDLE block
        if (order[i].startTime > previousFinish)
        {
            printf("+--------");
        }

        // Process block
        printf("+--------");
    }

    printf("+\n");

    // -------------------------------
    // PROCESS / IDLE LABELS
    // -------------------------------

    previousFinish = 0;

    printf("|");

    for (int i = 0; i < n; i++)
    {
        // CPU was idle before this process
        if (order[i].startTime > previousFinish)
        {
            printf("  IDLE  |");
        }

        // Process
        printf("   P%d   |", order[i].pid);

        previousFinish = order[i].completionTime;
    }

    printf("\n");

    // -------------------------------
    // BOTTOM BORDER
    // -------------------------------

    previousFinish = 0;

    for (int i = 0; i < n; i++)
    {
        if (order[i].startTime > previousFinish)
        {
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

    for (int i = 0; i < n; i++)
    {
        // Start of an idle period
        if (order[i].startTime > previousFinish)
        {
            printf("%-8d", order[i].startTime);
        }

        // Process completion
        printf("%-8d", order[i].completionTime);

        previousFinish = order[i].completionTime;
    }

    printf("\n");
}

// Gantt Chart for Round Robin, srtf
void printSegmentGanttChart(ScheduleSegment segments[], int count)
{
    printf("\nGantt Chart\n");

    if (count <= 0)
    {
        printf("No execution segments to display.\n");
        return;
    }

    // Print the top border
    for (int i = 0; i < count; i++)
    {
        printf("+--------");
    }
    printf("+\n");

    // Print process labels
    printf("|");

    for (int i = 0; i < count; i++)
    {
        if (segments[i].pid == 0)
        {
            printf("  IDLE  |");
        }
        else
        {
            printf("   P%-4d|", segments[i].pid);
        }
    }

    printf("\n");

    // Print the bottom border
    for (int i = 0; i < count; i++)
    {
        printf("+--------");
    }
    printf("+\n");

    // Print timestamps
    printf("%-8d", segments[0].startTime);

    for (int i = 0; i < count; i++)
    {
        printf("%-8d", segments[i].endTime);
    }

    printf("\n");
}
