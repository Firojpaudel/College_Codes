#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

int calculateSeekTime(int requests[], int n, int initialHead) {
    int totalSeekTime = 0;
    int currentHead = initialHead;

    printf("\n+--------------------------------------------------+\n");
    printf("|              Seek Time Calculation               |\n");
    printf("+--------------------------------------------------+\n");
    printf("| From Track | To Track | Seek Time                |\n");
    printf("+------------+----------+--------------------------+\n");

    for (int i = 0; i < n; i++) {
        int seekTime = abs(requests[i] - currentHead);
        totalSeekTime += seekTime;
        printf("|     %4d   |   %4d   |          %4d            |\n", currentHead, requests[i], seekTime);
        currentHead = requests[i];
    }

    printf("+------------+----------+--------------------------+\n");
    return totalSeekTime;
}

int main() {
    int n, requests[MAX_REQUESTS], initialHead;

    printf("+------------------------------------------+\n");
    printf("+            FCFS Disk Scheduling         +\n");
    printf("+------------------------------------------+\n");
    printf("\n");
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    int totalSeekTime = calculateSeekTime(requests, n, initialHead);

    // Display results
    printf("\nTotal Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
    printf("\n");
    printf("Compiled By: Firoj Paudel\n");

    return 0;
}
