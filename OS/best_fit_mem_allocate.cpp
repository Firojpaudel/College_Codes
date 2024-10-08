#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 100
#define COLUMN_WIDTH 20

// Function to print the memory partitions
void printMemory(int partitions[], int partitionSize)
{
    for (int i = 0; i < partitionSize; i++)
    {
        printf("%4d ", partitions[i]); // Fixed-width format for consistent alignment
    }
}

// Function to find the best-fit partition for a process
int findBestFit(int partitions[], int partitionSize, int processSize)
{
    int bestFitIndex = -1;
    int smallestFit = 1e9; // Arbitrarily large value for initial comparison

    for (int i = 0; i < partitionSize; i++)
    {
        if (partitions[i] >= processSize && partitions[i] < smallestFit)
        {
            smallestFit = partitions[i];
            bestFitIndex = i;
        }
    }

    return bestFitIndex;
}

// Function to allocate memory using Best Fit Allocation strategy
void bestFitMemoryAllocation(int partitions[], int partitionSize, int processRequests[], int numProcesses)
{
    int originalPartitions[MAX_PARTITIONS];

    // Store original partition sizes for display after allocation
    for (int i = 0; i < partitionSize; i++)
        originalPartitions[i] = partitions[i];

    // Printing table header
    printf("\n");
    printf("+------------------+-------------------------------+-------------------------------+------------+\n");
    printf("| Process Request  | Memory Partitions (Before)    | Memory Partitions (After)     | Allocated? |\n");
    printf("+------------------+-------------------------------+-------------------------------+------------+\n");

    for (int i = 0; i < numProcesses; i++)
    {
        int processSize = processRequests[i];
        int bestFitIndex = findBestFit(partitions, partitionSize, processSize);
        int allocated = (bestFitIndex != -1);

        // If found, allocate the process and reduce the partition size
        if (allocated)
        {
            partitions[bestFitIndex] -= processSize;
        }

        // Printing current row
        printf("| %16d | ", processSize);
        printMemory(originalPartitions, partitionSize);
        printf("     | ");
        printMemory(partitions, partitionSize);
        printf("     | %10s |\n", allocated ? "Yes" : "No");
    }

    // Printing table footer
    printf("+------------------+-------------------------------+-------------------------------+------------+\n");
}

int main()
{
    int numProcesses, partitionSize;

    printf("+------------------------------------------+\n");
    printf("+        Best Fit Memory Allocation        +\n");
    printf("+------------------------------------------+\n");

    // Input the number of memory partitions
    printf("Enter the number of memory partitions: ");
    scanf("%d", &partitionSize);

    // Allocate memory for partitions
    int *partitions = (int *)malloc(partitionSize * sizeof(int));
    if (partitions == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Input the partition sizes
    printf("Enter the memory partitions (space sizes): ");
    for (int i = 0; i < partitionSize; i++)
    {
        scanf("%d", &partitions[i]);
    }

    // Input the number of process requests
    printf("Enter the number of process requests: ");
    scanf("%d", &numProcesses);

    // Allocate memory for process requests
    int *processRequests = (int *)malloc(numProcesses * sizeof(int));
    if (processRequests == NULL)
    {
        printf("Memory allocation failed.\n");
        free(partitions);
        return 1;
    }

    // Input the process sizes
    printf("Enter the process requests (sizes): ");
    for (int i = 0; i < numProcesses; i++)
    {
        scanf("%d", &processRequests[i]);
    }

    // Validate partition size
    if (partitionSize <= 0 || partitionSize > MAX_PARTITIONS)
    {
        printf("Invalid partition size.\n");
        free(partitions);
        free(processRequests);
        return 1;
    }

    // Call function to perform Best Fit Allocation
    bestFitMemoryAllocation(partitions, partitionSize, processRequests, numProcesses);

    // Free dynamically allocated memory
    free(partitions);
    free(processRequests);

    printf("Compiled By: Firoj Paudel\n");

    return 0;
}
