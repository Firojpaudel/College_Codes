#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100

void printFrames(int frames[], int frameSize)
{
    for (int i = 0; i < frameSize; i++)
    {
        if (frames[i] == -1)
            printf("[ ] "); // Display empty frame
        else
            printf("[%d] ", frames[i]);
    }
}

int pageFaultsFIFO(int pages[], int numPages, int frameSize)
{
    int frames[MAX_PAGES]; // Initialize frames array
    for (int i = 0; i < frameSize; i++) // Ensure all elements are set to -1
        frames[i] = -1;

    int pageFaults = 0;
    int nextFrame = 0;

    for (int i = 0; i < numPages; i++)
    {
        int pageFound = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frameSize; j++)
        {
            if (frames[j] == pages[i])
            {
                pageFound = 1;
                break;
            }
        }

        // If page not found, we need to replace a page
        if (!pageFound)
        {
            // Replace the oldest page (FIFO)
            frames[nextFrame] = pages[i]; // Place the new page
            nextFrame = (nextFrame + 1) % frameSize; // Move to the next frame
            pageFaults++; // Increment page fault count
        }

        // Print current state of frames
        printf("| ");
        printFrames(frames, frameSize);
        printf("|   %s          |\n", pageFound ? "No " : "Yes");
    }

    return pageFaults;
}

int main()
{
    int numPages, frameSize;
    int pages[MAX_PAGES];

    printf("+------------------------------------------+\n");
    printf("+          Belady's Anomaly Demo          +\n");
    printf("+------------------------------------------+\n");

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &numPages);

    printf("Enter the page reference string (space separated): ");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    printf("\nUsing %d frames:\n", frameSize);
    printf("+-------------+----------------+\n");
    printf("| Frame State |    Page Fault  |\n");
    printf("+-------------+----------------+\n");
    int pageFaults = pageFaultsFIFO(pages, numPages, frameSize);
    printf("+-------------+----------------+\n");
    printf("Total Page Faults with %d frames: %d\n", frameSize, pageFaults);

    // Demonstrating Belady's Anomaly
    printf("\nNow increasing the number of frames to %d:\n", frameSize + 1);
    printf("+-----------------+----------------+\n");
    printf("| Frame State     |    Page Fault  |\n");
    printf("+-----------------+----------------+\n");
    pageFaults = pageFaultsFIFO(pages, numPages, frameSize + 1);
    printf("+-----------------+----------------+\n");
    printf("Total Page Faults with %d frames: %d\n", frameSize + 1, pageFaults);

    printf("Compiled By: Firoj Paudel\n");

    return 0;
}
