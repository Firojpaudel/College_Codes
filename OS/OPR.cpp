#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100
#define COLUMN_WIDTH 20

void printFrames(int frames[], int frameSize)
{
    for (int i = 0; i < frameSize; i++)
    {
        if (frames[i] != -1)
            printf("%-*d", COLUMN_WIDTH / frameSize, frames[i]); // Adjusting column width for better alignment
        else
            printf("%-*c", COLUMN_WIDTH / frameSize, '_'); // Adjusting column width for better alignment
    }
}

int isPageInFrames(int frames[], int frameSize, int page)
{
    for (int i = 0; i < frameSize; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

int findOptimalVictim(int frames[], int frameSize, int pageReferences[], int currentIndex, int numReferences)
{
    int farthest = currentIndex;
    int victim = 0;

    for (int i = 0; i < frameSize; i++)
    {
        int j;
        for (j = currentIndex + 1; j < numReferences; j++)
        {
            if (frames[i] == pageReferences[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    victim = i;
                }
                break;
            }
        }
        if (j == numReferences)
        {
            return i; // This page will not be used again, so it's the optimal victim
        }
    }
    return victim;
}

void oprPageReplacement(int pageReferences[], int numReferences, int frameSize)
{
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    // Print table header
    printf("\n");
    printf("+--------------------+--------------------+------------+\n");
    printf("| Page Reference     | Frame Contents     | Page Fault |\n");
    printf("+--------------------+--------------------+------------+\n");

    for (int i = 0; i < numReferences; i++)
    {
        int page = pageReferences[i];
        int pageFault = !isPageInFrames(frames, frameSize, page);

        // Update frames if page fault occurs
        if (pageFault)
        {
            int victim = findOptimalVictim(frames, frameSize, pageReferences, i, numReferences);
            frames[victim] = page;
            pageFaults++;
        }

        // Print current row
        printf("| %18d | ", page);
        printFrames(frames, frameSize);
        printf(" | %10s |\n", pageFault ? "Yes" : "No");
    }

    // Printing table footer
    printf("+--------------------+--------------------+------------+\n");
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main()
{
    int numReferences, frameSize;

    printf("+------------------------------------+\n");
    printf("+        Optimal Page Replacement    +\n");
    printf("+------------------------------------+\n");

    printf("Enter the number of page references: ");
    scanf("%d", &numReferences);

    int *pageReferences = (int *)malloc(numReferences * sizeof(int));
    if (pageReferences == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the page references: ");
    for (int i = 0; i < numReferences; i++)
    {
        scanf("%d", &pageReferences[i]);
    }

    printf("Enter the page frame size: ");
    scanf("%d", &frameSize);

    if (frameSize <= 0 || frameSize > MAX_FRAMES)
    {
        printf("Invalid page frame size.\n");
        free(pageReferences);
        return 1;
    }

    oprPageReplacement(pageReferences, numReferences, frameSize);

    free(pageReferences);
    return 0;
}
