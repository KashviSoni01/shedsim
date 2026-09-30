#include <stdio.h>
#include "process.h"


// Function to sort processes by arrival time
void sortByArrival(Process processes[], int n) {

    for(int i=0; i<n; i++) {

        for(int j=0; j<n-i-1; j++) {

            if(processes[j].arrivalTime > processes[j+1].arrivalTime) {

                Process temp = processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
}


int main() {

    int n;
    Process processes[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);


    // Take process information from the user
    for (int i = 0; i < n; i++) {

        processes[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);

        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);

        printf("Priority: ");
        scanf("%d", &processes[i].priority);

        // Initially, remaining time = burst time
        processes[i].remainingTime = processes[i].burstTime;
    }


    // Sort processes by arrival time
    sortByArrival(processes, n);



    printf("\n--------------------------------\n");
    printf("PID   Arrival   Burst   Priority\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; i++) {

        printf("P%d      %d        %d        %d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority);
    }


    return 0;
}