#include <stdio.h>

#define MAX_SEGMENTS 100

struct Segment
{
    int segmentNumber;
    int base;
    int limit;
};

void displaySegmentTable(struct Segment segments[], int segmentCount)
{
    printf("\n+--------------------------------------------------+\n");
    printf("|                 Segment Table                    |\n");
    printf("+--------------------------------------------------+\n");
    printf("| Segment No | Base Address | Limit                |\n");
    printf("+------------+--------------+----------------------+\n");
    for (int i = 0; i < segmentCount; i++)
    {
        printf("|     %4d   |    %6d   |      %6d           |\n", segments[i].segmentNumber, segments[i].base, segments[i].limit);
    }
    printf("+------------+--------------+----------------------+\n");
}

void calculatePhysicalAddress(struct Segment segments[], int segmentCount, int segNo, int logicalAddr)
{
    for (int i = 0; i < segmentCount; i++)
    {
        if (segments[i].segmentNumber == segNo)
        {
            if (logicalAddr < segments[i].limit)
            {
                int physicalAddress = segments[i].base + logicalAddr;
                printf("\n+--------------------------------------------------+\n");
                printf("|             Physical Address Calculation         |\n");
                printf("+--------------------------------------------------+\n");
                printf("| Segment No | Logical Address | Physical Address  |\n");
                printf("+------------+-----------------+-------------------+\n");
                printf("|     %4d   |       %6d    |       %6d      |\n", segNo, logicalAddr, physicalAddress);
                printf("+------------+-----------------+-------------------+\n");
            }
            else
            {
                printf("Error: Logical address exceeds the segment limit!\n");
            }
            return;
        }
    }
    printf("Error: Segment not found!\n");
}

int main()
{
    int segmentCount, segNo, logicalAddr;
    struct Segment segments[MAX_SEGMENTS];

    printf("+------------------------------------------+\n");
    printf("+           Segment Table Program          +\n");
    printf("+------------------------------------------+\n");

    // Input the number of segments
    printf("Enter the number of segments: ");
    scanf("%d", &segmentCount);

    // Input details for each segment
    for (int i = 0; i < segmentCount; i++)
    {
        printf("Enter details for segment %d:\n", i + 1);
        printf("  Segment No: ");
        scanf("%d", &segments[i].segmentNumber);
        printf("  Base Address: ");
        scanf("%d", &segments[i].base);
        printf("  Limit: ");
        scanf("%d", &segments[i].limit);
    }

    // Display the segment table
    displaySegmentTable(segments, segmentCount);

    // Input the segment number and logical address for translation
    printf("\nEnter the segment number for logical address translation: ");
    scanf("%d", &segNo);
    printf("Enter the logical address: ");
    scanf("%d", &logicalAddr);

    // Calculate the physical address
    calculatePhysicalAddress(segments, segmentCount, segNo, logicalAddr);

    printf("\nCompiled By: Firoj Paudel\n");

    return 0;
}
