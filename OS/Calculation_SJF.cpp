#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

void calculateTATandWT(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    // Calculate Waiting Time
    waitingTime[0] = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }
}

void printGanttChart(int processes[], int n, int burstTime[]) {
    int currentTime = 0;
    printf("\nGantt Chart:\n\n");
    
    // Print top border
    printf("+");
    for (int i = 0; i < n; i++) {
        printf("----+");
    }
    printf("\n|");
    
    // Print process IDs
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i]);
        currentTime += burstTime[i];
    }
    
    printf("\n+");
    for (int i = 0; i < n; i++) {
        printf("----+");
    }
    printf("\n0");

    // Print end times
    currentTime = 0;
    for (int i = 0; i < n; i++) {
        currentTime += burstTime[i];
        printf("    %d", currentTime);
    }
    printf("\n");
}

void sortProcesses(int processes[], int burstTime[], int n) {
    // Sort processes based on burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if the burst time of the next process is less
            if (burstTime[j] > burstTime[j + 1]) {
                // Swap burst time
                int tempBT = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = tempBT;

                // Swap process IDs
                int tempP = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempP;
            }
        }
    }
}

int main() {
    int n, processes[MAX_PROCESSES], burstTime[MAX_PROCESSES], waitingTime[MAX_PROCESSES], turnaroundTime[MAX_PROCESSES];

    printf("+------------------------------------------+\n");
    printf("+        SJF Scheduling Algorithm          +\n");
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

    // Sort processes by burst time
    sortProcesses(processes, burstTime, n);
    calculateTATandWT(processes, n, burstTime, waitingTime, turnaroundTime);

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

    printGanttChart(processes, n, burstTime);

    printf("Compiled By: Firoj Paudel\n");

    return 0;
}
