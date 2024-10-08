#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

void calculateTATandWT(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[], int quantum) {
    int remainingTime[MAX_PROCESSES];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
        waitingTime[i] = 0; // Initialize waiting time
    }

    int t = 0; // Current time
    while (1) {
        int done = 1; // Check if all processes are done
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0; // There is a pending process
                if (remainingTime[i] > quantum) {
                    t += quantum; // Increase time by quantum
                    remainingTime[i] -= quantum; // Decrease remaining time
                } else {
                    t += remainingTime[i]; // Increase time by remaining time
                    waitingTime[i] += (t - burstTime[i]); // Calculate waiting time
                    remainingTime[i] = 0; // Process finished
                }
            }
        }
        if (done == 1) break; // Exit if all processes are done
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

void printGanttChart(int processes[], int n, int burstTime[], int quantum) {
    int remainingTime[MAX_PROCESSES];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
    }

    int t = 0; // Current time
    printf("\nGantt Chart:\n\n");

    printf("+");

    // Variables to track the number of times the process has been executed
    int ganttOrder[MAX_PROCESSES * 100];  // To store the order of process executions
    int ganttTimes[MAX_PROCESSES * 100];  // To store the corresponding end times
    int ganttIndex = 0;  // Tracks the number of entries in the Gantt chart

    while (1) {
        int done = 1; // Check if all processes are done
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0; // There is a pending process
                if (remainingTime[i] > quantum) {
                    ganttOrder[ganttIndex] = processes[i];
                    t += quantum; // Increase time by quantum
                    ganttTimes[ganttIndex] = t;
                    ganttIndex++;
                    remainingTime[i] -= quantum; // Decrease remaining time
                } else {
                    ganttOrder[ganttIndex] = processes[i];
                    t += remainingTime[i]; // Increase time by remaining time
                    ganttTimes[ganttIndex] = t;
                    ganttIndex++;
                    remainingTime[i] = 0; // Process finished
                }
            }
        }
        if (done == 1) break; // Exit if all processes are done
    }

    // Print the top of the Gantt chart
    for (int i = 0; i < ganttIndex; i++) {
        printf("----+");
    }
    printf("\n|");

    // Print the process IDs in order
    for (int i = 0; i < ganttIndex; i++) {
        printf(" P%d |", ganttOrder[i]);
    }
    
    printf("\n+");
    for (int i = 0; i < ganttIndex; i++) {
        printf("----+");
    }
    printf("\n0");

    // Print the end times below the Gantt chart
    for (int i = 0; i < ganttIndex; i++) {
        printf("   %d", ganttTimes[i]);
    }
    printf("\n");
}

int main() {
    int n, processes[MAX_PROCESSES], burstTime[MAX_PROCESSES], waitingTime[MAX_PROCESSES], turnaroundTime[MAX_PROCESSES], quantum;

    printf("+------------------------------------------+\n");
    printf("+        Round Robin Scheduling            +\n");
    printf("+------------------------------------------+\n");
    printf("\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the process IDs (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i]);
    }

    printf("Enter the burst times for each process (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burstTime[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    calculateTATandWT(processes, n, burstTime, waitingTime, turnaroundTime, quantum);

    // Calculate total waiting time and turnaround time
    int totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    // Calculate averages
    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    // Display results
    printf("\n+-------------------+-----------------------+\n");
    printf("| Process ID        | Waiting Time          |\n");
    printf("+-------------------+-----------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %16d  | %17d     |\n", processes[i], waitingTime[i]);
    }
    printf("+-------------------+-----------------------+\n");
    printf("Total Waiting Time: %d\n", totalWT);
    printf("Average Waiting Time: %.2f\n", averageWT);

    printf("\n+----------------------+---------------------+\n");
    printf("| Process ID           | Turnaround Time     |\n");
    printf("+----------------------+---------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %16d     | %17d   |\n", processes[i], turnaroundTime[i]);
    }
    printf("+----------------------+---------------------+\n");
    printf("Total Turnaround Time: %d\n", totalTAT);
    printf("Average Turnaround Time: %.2f\n", averageTAT);

    printGanttChart(processes, n, burstTime, quantum);

    printf("Compiled By: Firoj Paudel\n");

    return 0;
}
