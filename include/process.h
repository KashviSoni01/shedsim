#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;

    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;

    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    int startTime;

    int started;
} Process;

#endif