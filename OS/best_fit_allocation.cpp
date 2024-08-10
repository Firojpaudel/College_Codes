#include <iostream>
#include <iomanip>
#include <climits> 

#define MAX_BLOCKS 100
#define COLUMN_WIDTH 20

using namespace std;

class MemoryBlock {
public:
    int size;
    bool allocated;
    int processId;

    MemoryBlock(int s = 0) : size(s), allocated(false), processId(0) {}
};

void printMemoryBlocks(MemoryBlock blocks[], int numBlocks) {
    for (int i = 0; i < numBlocks; ++i) {
        if (blocks[i].allocated)
            cout << setw(COLUMN_WIDTH) << blocks[i].size;
        else
            cout << setw(COLUMN_WIDTH) << '_';
    }
}

int findBestFitBlock(MemoryBlock blocks[], int numBlocks, int requestSize) {
    int bestFitIndex = -1;
    int minSize = INT_MAX;

    for (int i = 0; i < numBlocks; ++i) {
        if (!blocks[i].allocated && blocks[i].size >= requestSize && blocks[i].size < minSize) {
            minSize = blocks[i].size;
            bestFitIndex = i;
        }
    }

    return bestFitIndex;
}

void bestFitMemoryAllocation(MemoryBlock blocks[], int numBlocks, int processRequests[], int numRequests) {
    int totalAllocated = 0;
    int totalBlocksAllocated = 0;

    // Print table header
    cout << "\n";
    cout << "+--------------------+--------------------+--------------+--------------------+\n";
    cout << "| Process Request    | Block Allocation   | Block Sizes  | Free Memory Blocks |\n";
    cout << "+--------------------+--------------------+--------------+--------------------+\n";

    for (int i = 0; i < numRequests; ++i) {
        int requestSize = processRequests[i];
        int blockIndex = findBestFitBlock(blocks, numBlocks, requestSize);

        cout << "| " << setw(18) << requestSize << " | ";
        if (blockIndex != -1) {
            blocks[blockIndex].allocated = true;
            blocks[blockIndex].processId = i + 1;
            totalBlocksAllocated++;
            totalAllocated += requestSize;
        } else {
            cout << "Not Allocated | ";
        }
        printMemoryBlocks(blocks, numBlocks);
        cout << " | " << setw(10) << totalAllocated << " |\n";
    }

    // Printing table footer
    cout << "+--------------------+--------------------+--------------+--------------------+\n";
    cout << "\nTotal Blocks Allocated: " << totalBlocksAllocated << "\n";
    cout << "Total Memory Allocated: " << totalAllocated << "\n";
}

int main() {
    int numBlocks, numRequests;

    cout << "+------------------------------------+\n";
    cout << "+        Best Fit Memory Allocation   +\n";
    cout << "+------------------------------------+\n";

    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;

    if (numBlocks > MAX_BLOCKS) {
        cout << "Number of blocks exceeds maximum limit.\n";
        return 1;
    }

    MemoryBlock blocks[MAX_BLOCKS];

    cout << "Enter the sizes of the memory blocks:\n";
    for (int i = 0; i < numBlocks; ++i) {
        int size;
        cout << "Block " << (i + 1) << " size: ";
        cin >> size;
        blocks[i] = MemoryBlock(size);
    }

    cout << "Enter the number of process requests: ";
    cin >> numRequests;

    if (numRequests > MAX_BLOCKS) {
        cout << "Number of requests exceeds maximum limit.\n";
        return 1;
    }

    int processRequests[MAX_BLOCKS];

    cout << "Enter the process request sizes:\n";
    for (int i = 0; i < numRequests; ++i) {
        cout << "Request " << (i + 1) << " size: ";
        cin >> processRequests[i];
    }

    bestFitMemoryAllocation(blocks, numBlocks, processRequests, numRequests);

    return 0;
}
