#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void calculateSeekTime(int requests[], int n, int initialHead, int totalTracks) {
    int totalSeekTime = 0;
    int currentHead = initialHead;
    
    // Create an array to store the order of service
    int order[MAX_REQUESTS];
    int orderIndex = 0;

    // Sort requests for SCAN algorithm
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Move towards the end of the disk first
    for (int i = 0; i < n; i++) {
        if (requests[i] >= currentHead) {
            totalSeekTime += abs(requests[i] - currentHead);
            order[orderIndex++] = currentHead;  // Add current head position
            order[orderIndex++] = requests[i];   // Move to request
            currentHead = requests[i];
        }
    }

    // Move to the end of the disk (totalTracks - 1)
    if (currentHead < totalTracks - 1) {
        totalSeekTime += abs(currentHead - (totalTracks - 1));
        order[orderIndex++] = currentHead;  // Add current head position
        order[orderIndex++] = totalTracks - 1; // Move to the end of the disk
        currentHead = totalTracks - 1;
    }

    // Move left towards the start of the disk
    for (int i = n - 1; i >= 0; i--) {
        if (requests[i] < initialHead) {
            totalSeekTime += abs(requests[i] - currentHead);
            order[orderIndex++] = currentHead;  // Add current head position
            order[orderIndex++] = requests[i];   // Move to request
            currentHead = requests[i];
        }
    }

    // Print the seek time calculation
    printf("\n+--------------------------------------------------+\n");
    printf("|              Seek Time Calculation               |\n");
    printf("+--------------------------------------------------+\n");
    printf("| From Track | To Track | Seek Time                |\n");
    printf("+------------+----------+--------------------------+\n");
    
    for (int i = 0; i < orderIndex - 1; i += 2) {
        printf("|     %4d   |   %4d   |          %4d            |\n", order[i], order[i + 1], abs(order[i + 1] - order[i]));
    }
    
    printf("+------------+----------+--------------------------+\n");
    printf("Total Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float)totalSeekTime / (orderIndex / 2)); // divide by number of movements
}

int main() {
    int n, requests[MAX_REQUESTS], initialHead, totalTracks;

    printf("+------------------------------------------+\n");
    printf("+             SCAN Disk Scheduling        +\n");
    printf("+------------------------------------------+\n");
    printf("\n");
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the total number of tracks: ");
    scanf("%d", &totalTracks);

    printf("Enter the requests (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    calculateSeekTime(requests, n, initialHead, totalTracks);
    printf("\nCompiled By: Firoj Paudel\n");

    return 0;
}
