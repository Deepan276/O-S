#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    // File descriptor using fcntl
    int fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Changing the file status flags using fcntl
    int flags = fcntl(fd, F_GETFL);
    flags |= O_APPEND; // Appending to the file
    fcntl(fd, F_SETFL, flags);

    // Writing data to the file using write
    const char *text = "Hello, this is a sample text.\n";
    ssize_t bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Seeking to a specific position using lseek
    off_t offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1) {
        perror("Error seeking in file");
        close(fd);
        return 1;
    }

    // Reading and displaying data using read
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0';
    printf("Read from file: %s\n", buffer);

    close(fd);

    // Using stat to get file information
    struct stat file_info;
    if (stat("sample.txt", &file_info) == -1) {
        perror("Error getting file info");
        return 1;
    }
    printf("File size: %lld bytes\n", (long long)file_info.st_size);
    printf("File permissions: %o\n", file_info.st_mode & 0777);

    // Using opendir and readdir to list directory contents
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    printf("Directory contents:\n");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}
