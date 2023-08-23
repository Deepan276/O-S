#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILES 10
#define MAX_FILE_NAME_LENGTH 20

struct File {
    char name[MAX_FILE_NAME_LENGTH];
    int size;
};

struct File files[MAX_FILES];
int num_files = 0;

void createFile(char name[], int size) {
    if (num_files >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    strcpy(files[num_files].name, name);
    files[num_files].size = size;
    num_files++;
    printf("File '%s' created with size %d.\n", name, size);
}

void deleteFile(char name[]) {
    bool found = false;

    for (int i = 0; i < num_files; i++) {
        if (strcmp(files[i].name, name) == 0) {
            printf("File '%s' deleted with size %d.\n", files[i].name, files[i].size);
            found = true;

            // Remove the file by shifting remaining files
            for (int j = i; j < num_files - 1; j++) {
                strcpy(files[j].name, files[j + 1].name);
                files[j].size = files[j + 1].size;
            }

            num_files--;
            break;
        }
    }

    if (!found) {
        printf("File '%s' not found.\n", name);
    }
}

void displayFiles() {
    printf("Files in the directory:\n");
    for (int i = 0; i < num_files; i++) {
        printf("File: %s, Size: %d\n", files[i].name, files[i].size);
    }
    printf("\n");
}

int main() {
    int choice;
    char name[MAX_FILE_NAME_LENGTH];
    int size;

    do {
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Display Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", name);
                printf("Enter file size: ");
                scanf("%d", &size);
                createFile(name, size);
                break;
            case 2:
                printf("Enter file name to delete: ");
                scanf("%s", name);
                deleteFile(name);
                break;
            case 3:
                displayFiles();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
