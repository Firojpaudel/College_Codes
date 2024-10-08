#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// Structure to represent a process
typedef struct {
    int id;          // Process ID
    int burstTime;   // Burst time
    int priority;    // Priority
    int waitingTime; // Waiting time
    int turnaroundTime; // Turnaround time
} Process;

// Function to compare processes based on priority
int compare(const void *a, const void *b) {
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;
    return processA->priority - processB->priority; // Higher priority comes first
}

// Function to calculate Turnaround Time and Waiting Time
void calculateTATandWT(Process processes[], int n) {
    // Calculate Waiting Time
    processes[0].waitingTime = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

// Function to print Gantt Chart
void printGanttChart(Process processes[], int n) {
    printf("\nGantt Chart:\n\n");

    printf("+");
    for (int i = 0; i < n; i++) {
        printf("----+");
    }
    printf("\n|");

    // Print process IDs
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].id);
    }

    printf("\n+");
    for (int i = 0; i < n; i++) {
        printf("----+");
    }
    printf("\n0");

    // Print end times
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        currentTime += processes[i].burstTime;
        printf("   %d", currentTime);
    }
    printf("\n");
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("+------------------------------------------+\n");
    printf("+         Priority Scheduling              +\n");
    printf("+------------------------------------------+\n");
    printf("\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the process IDs (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].id);
    }

    printf("Enter the burst times for each process (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].burstTime);
    }

    printf("Enter the priorities for each process (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].priority);
    }

    // Sort processes based on priority
    qsort(processes, n, sizeof(Process), compare);

    calculateTATandWT(processes, n);

    // Calculate total waiting time and turnaround time
    int totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }

    // Calculate averages
    float averageWT = (float)totalWT / n;
    float averageTAT = (float)totalTAT / n;

    // Display results
    printf("\n+-------------------+-----------------------+\n");
    printf("| Process ID        | Waiting Time          |\n");
    printf("+-------------------+-----------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %16d  | %17d     |\n", processes[i].id, processes[i].waitingTime);
    }
    printf("+-------------------+-----------------------+\n");
    printf("Total Waiting Time: %d\n", totalWT);
    printf("Average Waiting Time: %.2f\n", averageWT);

    printf("\n+----------------------+---------------------+\n");
    printf("| Process ID           | Turnaround Time     |\n");
    printf("+----------------------+---------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %16d     | %17d   |\n", processes[i].id, processes[i].turnaroundTime);
    }
    printf("+----------------------+---------------------+\n");
    printf("Total Turnaround Time: %d\n", totalTAT);
    printf("Average Turnaround Time: %.2f\n", averageTAT);

    printGanttChart(processes, n);

    printf("Compiled By: Firoj Paudel\n");

    return 0;
}
