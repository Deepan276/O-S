#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 1000
#define NUM_BLOCKS 5

struct MemoryBlock {
    int start;
    int size;
    int process_id;
};

struct Process {
    int id;
    int size;
};

struct MemoryBlock memory[MEMORY_SIZE];
struct Process processes[NUM_BLOCKS];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].start = i;
        memory[i].size = 0;
        memory[i].process_id = -1;
    }
}

void displayMemory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].size > 0) {
            printf("Start: %d, Size: %d, Process: %d\n",
                   memory[i].start, memory[i].size, memory[i].process_id);
        }
    }
    printf("\n");
}

void firstFit(int process_index) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].size >= processes[process_index].size && memory[i].process_id == -1) {
            memory[i].size = processes[process_index].size;
            memory[i].process_id = processes[process_index].id;
            break;
        }
    }
}

void bestFit(int process_index) {
    int best_fit_index = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].size >= processes[process_index].size && memory[i].process_id == -1) {
            if (best_fit_index == -1 || memory[i].size < memory[best_fit_index].size) {
                best_fit_index = i;
            }
        }
    }

    if (best_fit_index != -1) {
        memory[best_fit_index].size = processes[process_index].size;
        memory[best_fit_index].process_id = processes[process_index].id;
    }
}

void worstFit(int process_index) {
    int worst_fit_index = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].size >= processes[process_index].size && memory[i].process_id == -1) {
            if (worst_fit_index == -1 || memory[i].size > memory[worst_fit_index].size) {
                worst_fit_index = i;
            }
        }
    }

    if (worst_fit_index != -1) {
        memory[worst_fit_index].size = processes[process_index].size;
        memory[worst_fit_index].process_id = processes[process_index].id;
    }
}

int main() {
    initializeMemory();

    // Initialize processes
    for (int i = 0; i < NUM_BLOCKS; i++) {
        processes[i].id = i + 1;
        processes[i].size = (i + 1) * 100;
    }

    printf("Processes:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        printf("Process %d: Size %d\n", processes[i].id, processes[i].size);
    }
    printf("\n");

    // First Fit
    printf("First Fit Allocation:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        firstFit(i);
        displayMemory();
    }

    // Clear memory
    initializeMemory();

    // Best Fit
    printf("Best Fit Allocation:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        bestFit(i);
        displayMemory();
    }

    // Clear memory
    initializeMemory();

    // Worst Fit
    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        worstFit(i);
        displayMemory();
    }

    return 0;
}
