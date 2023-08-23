#include <stdio.h>
#include <stdlib.h>

struct FileRecord {
    int size;
};

int main() {
    int numFiles;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    struct FileRecord *files = (struct FileRecord *)malloc(numFiles * sizeof(struct FileRecord));

    for (int i = 0; i < numFiles; i++) {
        printf("Enter the size of file %d: ", i + 1);
        scanf("%d", &files[i].size);
    }

    int totalSpace = 1000; // Total disk space

    int currentAddress = 0;
    for (int i = 0; i < numFiles; i++) {
        if (currentAddress + files[i].size > totalSpace) {
            printf("Error: Not enough space for file %d\n", i + 1);
        } else {
            printf("File %d: Allocated at address %d, Size: %d\n", i + 1, currentAddress, files[i].size);
            currentAddress += files[i].size;
        }
    }

    free(files);
    return 0;
}
