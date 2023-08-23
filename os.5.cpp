#include <stdio.h>
#define MAX_PROCESSES 5

struct Process {
    int id;
    int priority;
    int burst_time;
};

void executeProcess(struct Process processes[], int n) {
    int highest_priority = -1;
    int selected_process = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].burst_time > 0 && processes[i].priority > highest_priority) {
            highest_priority = processes[i].priority;
            selected_process = i;
        }
    }

    if (selected_process != -1) {
        processes[selected_process].burst_time--;

        printf("Executing process %d (Priority: %d, Burst Time: %d)\n",
               processes[selected_process].id,
               processes[selected_process].priority,
               processes[selected_process].burst_time);
    }
}

int main() {
    struct Process processes[MAX_PROCESSES] = {
        {1, 3, 5},
        {2, 1, 3},
        {3, 4, 2},
        {4, 2, 4},
        {5, 5, 1}
    };

    int total_processes = sizeof(processes) / sizeof(processes[0]);

    while (1) {

        int all_completed = 1;
        for (int i = 0; i < total_processes; i++) {
            if (processes[i].burst_time > 0) {
                all_completed = 0;
                break;
            }
        }

        if (all_completed) {
            printf("All processes completed.\n");
            break;
        }

        executeProcess(processes, total_processes);
    }

    return 0;
}
