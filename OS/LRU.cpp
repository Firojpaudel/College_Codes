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

int findLRUVictim(int frameTimes[], int frameSize)
{
    int minTime = frameTimes[0];
    int victim = 0;

    for (int i = 1; i < frameSize; i++)
    {
        if (frameTimes[i] < minTime)
        {
            minTime = frameTimes[i];
            victim = i;
        }
    }

    return victim;
}

void lruPageReplacement(int pageReferences[], int numReferences, int frameSize)
{
    int frames[MAX_FRAMES];
    int frameTimes[MAX_FRAMES];
    int pageFaults = 0;
    int time = 0;

    // Initialize frames and times
    for (int i = 0; i < frameSize; i++)
    {
        frames[i] = -1;
        frameTimes[i] = 0;
    }

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
            int victim = -1;
            for (int j = 0; j < frameSize; j++)
            {
                if (frames[j] == -1)
                {
                    victim = j; // Empty frame found
                    break;
                }
            }

            if (victim == -1) // No empty frame, find LRU page to replace
            {
                victim = findLRUVictim(frameTimes, frameSize);
            }

            frames[victim] = page;
            frameTimes[victim] = time;
            pageFaults++;
        }
        else
        {
            // Update the time for the existing page
            for (int j = 0; j < frameSize; j++)
            {
                if (frames[j] == page)
                {
                    frameTimes[j] = time;
                    break;
                }
            }
        }

        // Print current row
        printf("| %18d | ", page);
        printFrames(frames, frameSize);
        printf(" | %10s |\n", pageFault ? "Yes" : "No");

        // Update time for the current reference
        time++;
    }

    // Printing table footer
    printf("+--------------------+--------------------+------------+\n");
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main()
{
    int numReferences, frameSize;

    printf("+------------------------------------+\n");
    printf("+        LRU Page Replacement        +\n");
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

    lruPageReplacement(pageReferences, numReferences, frameSize);

    free(pageReferences);
    return 0;
}
