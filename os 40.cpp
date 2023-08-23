#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat file_info;

    if (stat(filename, &file_info) == -1) {
        perror("Error getting file info");
        return 1;
    }

    printf("File Permissions: %o\n", file_info.st_mode & 0777);

    if (S_ISREG(file_info.st_mode)) {
        printf("File Type: Regular File\n");
    } else if (S_ISDIR(file_info.st_mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISLNK(file_info.st_mode)) {
        printf("File Type: Symbolic Link\n");
    } else {
        printf("File Type: Unknown\n");
    }

    printf("Owner User ID: %d\n", file_info.st_uid);
    printf("Owner Group ID: %d\n", file_info.st_gid);

    return 0;
}
