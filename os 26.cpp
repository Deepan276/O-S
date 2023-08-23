#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file, "%s", text);
    fclose(file);
}

void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main() {
    const char *filename = "file.txt";
    const char *text = "Hello, this is a sample text.\n";

    writeToFile(filename, text);
    printf("File contents:\n");
    readFromFile(filename);

    return 0;
}
