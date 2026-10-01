#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void sortByArrival(Process processes[], int n);

void fcfs(Process processes[], int n);

void printGanttChart(Process processes[], int n);

#endif