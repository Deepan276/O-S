#include <stdio.h>
#include <stdlib.h>

int main() {
    int numRequests, headPosition;
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);
    printf("Enter the current head position: ");
    scanf("%d", &headPosition);

    int *requests = (int *)malloc(numRequests * sizeof(int));
    printf("Enter the disk requests:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    int totalDistance = 0;

    printf("Seek Sequence: %d", headPosition);
    int currentHead = headPosition;

    int i = 0;
    while (i < numRequests) {
        if (requests[i] >= currentHead) {
            totalDistance += abs(requests[i] - currentHead);
            currentHead = requests[i];
            printf(" -> %d", currentHead);
            i++;
        } else {
            totalDistance += abs(199 - currentHead);
            currentHead = 0;
            printf(" -> 0");
        }
    }

    printf(" -> 199");
    totalDistance += abs(199 - currentHead);

    printf("\nTotal Head Movement: %d\n", totalDistance);

    free(requests);
    return 0;
}
