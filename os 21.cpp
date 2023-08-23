#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

int blockSizes[MAX_BLOCKS];
int processSizes[MAX_PROCESSES];
int allocation[MAX_PROCESSES];

void worstFit(int numBlocks, int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int maxBlockSize = -1;
        int index = -1;

        for (int j = 0; j < numBlocks; j++) {
            if (allocation[j] == -1 && blockSizes[j] >= processSizes[i] && blockSizes[j] > maxBlockSize) {
                maxBlockSize = blockSizes[j];
                index = j;
            }
        }

        if (index != -1) {
            allocation[index] = i;
        }
    }
}

int main() {
    int numBlocks, numProcesses;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);
    printf("Enter the size of memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        scanf("%d", &blockSizes[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the size of processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d", &processSizes[i]);
    }

    for (int i = 0; i < numBlocks; i++) {
        allocation[i] = -1;
    }

    worstFit(numBlocks, numProcesses);

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("%d\t\t%d\t\t", i, blockSizes[i]);
        if (allocation[i] != -1) {
            printf("%d", allocation[i]);
        } else {
            printf("Not Allocated");
        }
        printf("\n");
    }

    return 0;
}
