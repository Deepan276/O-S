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
    int direction = 1; // 1 for moving towards higher cylinder, -1 for moving towards lower cylinder
    int currentHead = headPosition;
    int i = 0;
    while (i < numRequests && currentHead >= 0 && currentHead <= 199) {
        if (requests[i] >= currentHead && direction == 1) {
            totalDistance += abs(requests[i] - currentHead);
            currentHead = requests[i];
            printf(" -> %d", currentHead);
            i++;
        } else if (requests[i] <= currentHead && direction == -1) {
            totalDistance += abs(requests[i] - currentHead);
            currentHead = requests[i];
            printf(" -> %d", currentHead);
            i--;
        } else {
            direction *= -1;
            if (direction == 1) {
                printf(" -> 199");
                totalDistance += abs(199 - currentHead);
                currentHead = 199;
            } else {
                printf(" -> 0");
                totalDistance += abs(0 - currentHead);
                currentHead = 0;
            }
        }
    }
    printf("\nTotal Head Movement: %d\n", totalDistance);

    free(requests);
    return 0;
}
