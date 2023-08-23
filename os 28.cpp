#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <search_pattern> <filename>\n", argv[0]);
        return 1;
    }

    const char *searchPattern = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchPattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);

    return 0;
}
