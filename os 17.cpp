#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

bool isSafe(int process, int num_resources) {
    for (int i = 0; i < num_resources; i++) {
        if (need[process][i] > available[i])
            return false;
    }
    return true;
}

bool requestResources(int process, int request[], int num_resources) {
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[process][i])
            return false;
    }

    for (int i = 0; i < num_resources; i++) {
        if (request[i] > available[i])
            return false;
    }

    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe(process, num_resources))
        return true;

    for (int i = 0; i < num_resources; i++) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }

    return false;
}

int main() {
    int num_processes, num_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources needed for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
        finished[i] = false;
    }

    int request[MAX_RESOURCES];
    int process;

    printf("Enter the process number (0 to %d) that is making a request: ", num_processes - 1);
    scanf("%d", &process);

    printf("Enter the resource request for process %d: ", process);
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &request[i]);
    }

    if (requestResources(process, request, num_resources)) {
        printf("Request granted. System is safe.\n");
    } else {
        printf("Request denied. System will be in an unsafe state.\n");
    }

    return 0;
}
