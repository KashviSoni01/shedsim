#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct {
    int pid;
    int startTime;
    int endTime;
} ScheduleSegment;

void sortByArrival(Process processes[], int n);

void fcfs(Process processes[], int n);

void sjf(Process processes[], int n);

int roundRobin(
    Process processes[],
    int n,
    int quantum,
    ScheduleSegment segments[]
);

void printGanttChart(Process processes[], int n);

void printRRGanttChart(ScheduleSegment segments[], int count);

#endif