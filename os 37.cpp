#include <stdio.h>
#include <stdlib.h>

int main() {
    int numRequests;
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int *requests = (int *)malloc(numRequests * sizeof(int));
    printf("Enter the disk requests:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    int currentHead = 0;
    int totalDistance = 0;

    printf("Seek Sequence: %d", currentHead);
    for (int i = 0; i < numRequests; i++) {
        totalDistance += abs(requests[i] - currentHead);
        currentHead = requests[i];
        printf(" -> %d", currentHead);
    }
    printf("\nTotal Head Movement: %d\n", totalDistance);

    free(requests);
    return 0;
}
