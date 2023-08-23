#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_DIRECTORIES 10
#define MAX_FILES_PER_DIRECTORY 10
#define MAX_DIRECTORY_NAME_LENGTH 20
#define MAX_FILE_NAME_LENGTH 20

struct File {
    char name[MAX_FILE_NAME_LENGTH];
    int size;
};

struct Directory {
    char name[MAX_DIRECTORY_NAME_LENGTH];
    struct File files[MAX_FILES_PER_DIRECTORY];
    int num_files;
};

struct Directory directories[MAX_DIRECTORIES];
int num_directories = 0;

void createDirectory(char name[]) {
    if (num_directories >= MAX_DIRECTORIES) {
        printf("Maximum number of directories reached.\n");
        return;
    }

    strcpy(directories[num_directories].name, name);
    directories[num_directories].num_files = 0;
    num_directories++;
    printf("Directory '%s' created.\n", name);
}

int findDirectory(char name[]) {
    for (int i = 0; i < num_directories; i++) {
        if (strcmp(directories[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void createFile(char directory_name[], char file_name[], int size) {
    int dir_index = findDirectory(directory_name);
    if (dir_index == -1) {
        printf("Directory '%s' not found.\n", directory_name);
        return;
    }

    struct Directory *dir = &directories[dir_index];
    if (dir->num_files >= MAX_FILES_PER_DIRECTORY) {
        printf("Directory '%s' is full. Cannot create more files.\n", directory_name);
        return;
    }

    struct File *file = &dir->files[dir->num_files];
    strcpy(file->name, file_name);
    file->size = size;
    dir->num_files++;

    printf("File '%s' created in directory '%s' with size %d.\n", file_name, directory_name, size);
}

void displayFilesInDirectory(char directory_name[]) {
    int dir_index = findDirectory(directory_name);
    if (dir_index == -1) {
        printf("Directory '%s' not found.\n", directory_name);
        return;
    }

    struct Directory *dir = &directories[dir_index];
    printf("Files in directory '%s':\n", directory_name);
    for (int i = 0; i < dir->num_files; i++) {
        printf("File: %s, Size: %d\n", dir->files[i].name, dir->files[i].size);
    }
    printf("\n");
}

int main() {
    int choice;
    char directory_name[MAX_DIRECTORY_NAME_LENGTH];
    char file_name[MAX_FILE_NAME_LENGTH];
    int size;

    do {
        printf("1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. Display Files in Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory name: ");
                scanf("%s", directory_name);
                createDirectory(directory_name);
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", directory_name);
                printf("Enter file name: ");
                scanf("%s", file_name);
                printf("Enter file size: ");
                scanf("%d", &size);
                createFile(directory_name, file_name, size);
                break;
            case 3:
                printf("Enter directory name: ");
                scanf("%s", directory_name);
                displayFilesInDirectory(directory_name);
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
