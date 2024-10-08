#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 100
#define COLUMN_WIDTH 20

void printMemory(int partitions[], int partitionSize)
{
    for (int i = 0; i < partitionSize; i++)
    {
        printf("%-*d", COLUMN_WIDTH / partitionSize, partitions[i]); // Adjusting column width for better alignment
    }
}

int findFirstFit(int partitions[], int partitionSize, int processSize)
{
    for (int i = 0; i < partitionSize; i++)
    {
        if (partitions[i] >= processSize) // Find first partition that fits the process
        {
            return i; // Return the index of the first fitting partition
        }
    }
    return -1; // No partition found
}

void firstFitMemoryAllocation(int partitions[], int partitionSize, int processRequests[], int numProcesses)
{
    int originalPartitions[MAX_PARTITIONS];

    // Storing original partition sizes for display after allocation
    for (int i = 0; i < partitionSize; i++)
        originalPartitions[i] = partitions[i];

    // Print table header
    printf("\n");
    printf("+---------------------+--------------------+---------------------+------------+\n");
    printf("| Process Request     | Memory Partitions  | Allocated (After)   | Allocated? |\n");
    printf("+---------------------+--------------------+---------------------+------------+\n");

    for (int i = 0; i < numProcesses; i++)
    {
        int processSize = processRequests[i];
        int firstFitIndex = findFirstFit(partitions, partitionSize, processSize);
        int allocated = (firstFitIndex != -1);

        // If found, allocate the process and reduce partition size
        if (allocated)
        {
            partitions[firstFitIndex] -= processSize;
        }

        // Print current row
        printf("| %18d  |", processSize);
        printMemory(originalPartitions, partitionSize);
        printf("| ");
        printMemory(partitions, partitionSize);
        printf("| %10s |\n", allocated ? "Yes" : "No");
    }

    // Printing table footer
    printf("+---------------------+--------------------+---------------------+------------+\n");
}

int main()
{
    int numProcesses, partitionSize;

    printf("+------------------------------------------+\n");
    printf("+         First Fit Memory Allocation      +\n");
    printf("+------------------------------------------+\n");

    printf("Enter the number of memory partitions: ");
    scanf("%d", &partitionSize);

    int *partitions = (int *)malloc(partitionSize * sizeof(int));
    if (partitions == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the memory partitions (space sizes): ");
    for (int i = 0; i < partitionSize; i++)
    {
        scanf("%d", &partitions[i]);
    }

    printf("Enter the number of process requests: ");
    scanf("%d", &numProcesses);

    int *processRequests = (int *)malloc(numProcesses * sizeof(int));
    if (processRequests == NULL)
    {
        printf("Memory allocation failed.\n");
        free(partitions);
        return 1;
    }

    printf("Enter the process requests (sizes): ");
    for (int i = 0; i < numProcesses; i++)
    {
        scanf("%d", &processRequests[i]);
    }

    if (partitionSize <= 0 || partitionSize > MAX_PARTITIONS)
    {
        printf("Invalid partition size.\n");
        free(partitions);
        free(processRequests);
        return 1;
    }

    firstFitMemoryAllocation(partitions, partitionSize, processRequests, numProcesses);

    free(partitions);
    free(processRequests);

    printf("Compiled By: Firoj Paudel\n");
    
    return 0;
}
