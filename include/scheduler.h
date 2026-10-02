#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void sortByArrival(Process processes[], int n);

void fcfs(Process processes[], int n);

void sjf(Process processes[], int n);

void roundRobin(Process processes[], int n, int quantum);

void printGanttChart(Process processes[], int n);

#endif