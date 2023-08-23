#include <stdio.h>
#include <stdlib.h>

struct FileRecord {
    int numBlocks;
    int *blockIndexes;
};

int main() {
    int numFiles, numBlocks;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);
    printf("Enter the number of blocks per file: ");
    scanf("%d", &numBlocks);

    struct FileRecord *files = (struct FileRecord *)malloc(numFiles * sizeof(struct FileRecord));

    for (int i = 0; i < numFiles; i++) {
        files[i].numBlocks = numBlocks;
        files[i].blockIndexes = (int *)malloc(numBlocks * sizeof(int));
        printf("Enter block indexes for file %d:\n", i + 1);
        for (int j = 0; j < numBlocks; j++) {
            scanf("%d", &files[i].blockIndexes[j]);
        }
    }

    printf("File Index Block Mapping:\n");
    for (int i = 0; i < numFiles; i++) {
        printf("File %d: ", i + 1);
        for (int j = 0; j < numBlocks; j++) {
            printf("%d ", files[i].blockIndexes[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < numFiles; i++) {
        free(files[i].blockIndexes);
    }
    free(files);
    return 0;
}
