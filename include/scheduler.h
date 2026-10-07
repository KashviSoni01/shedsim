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

int srtf(Process processes[], int n, ScheduleSegment segments[]);

void priorityScheduling(Process processes[], int n);
int preemptivePriority(Process processes[], int n, ScheduleSegment segments[]);

int roundRobin(
    Process processes[],
    int n,
    int quantum,
    ScheduleSegment segments[]
);

void printGanttChart(Process processes[], int n);

void printSegmentGanttChart(ScheduleSegment segments[], int count);

#endif