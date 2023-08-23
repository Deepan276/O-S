#include <stdio.h>
#include <stdlib.h>

struct Block {
    int data;
    struct Block *next;
};

struct FileRecord {
    struct Block *firstBlock;
    struct Block *lastBlock;
};

void addBlock(struct FileRecord *file, int data) {
    struct Block *newBlock = (struct Block *)malloc(sizeof(struct Block));
    newBlock->data = data;
    newBlock->next = NULL;

    if (file->lastBlock == NULL) {
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }
}

void printBlocks(struct FileRecord *file) {
    struct Block *currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        printf("%d -> ", currentBlock->data);
        currentBlock = currentBlock->next;
    }
    printf("NULL\n");
}

int main() {
    int numFiles, numBlocks;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);
    printf("Enter the number of blocks per file: ");
    scanf("%d", &numBlocks);

    struct FileRecord *files = (struct FileRecord *)malloc(numFiles * sizeof(struct FileRecord));

    for (int i = 0; i < numFiles; i++) {
        files[i].firstBlock = NULL;
        files[i].lastBlock = NULL;
        printf("Enter block indexes for file %d:\n", i + 1);
        for (int j = 0; j < numBlocks; j++) {
            int data;
            scanf("%d", &data);
            addBlock(&files[i], data);
        }
    }

    printf("File Block Mapping:\n");
    for (int i = 0; i < numFiles; i++) {
        printf("File %d: ", i + 1);
        printBlocks(&files[i]);
    }

    for (int i = 0; i < numFiles; i++) {
        struct Block *currentBlock = files[i].firstBlock;
        while (currentBlock != NULL) {
            struct Block *temp = currentBlock;
            currentBlock = currentBlock->next;
            free(temp);
        }
    }
    free(files);
    return 0;
}
