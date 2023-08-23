#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd; // File descriptor

    // Creating a new file or opening an existing one
    fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Writing data to the file
    const char *text = "Hello, this is a sample text.";
    ssize_t bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Closing the file
    close(fd);

    // Opening the file for reading
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Reading data from the file and displaying it
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';
    printf("Read from file: %s\n", buffer);

    // Closing the file
    close(fd);

    // Deleting the file
    if (remove("sample.txt") == -1) {
        perror("Error deleting file");
        return 1;
    }

    printf("File deleted.\n");

    return 0;
}
