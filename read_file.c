#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    struct stat file_info;

    int result;

    // Use stdin (file descriptor 0) for reading
    int file_descriptor = 0; // 0 represents stdin

    __asm__ volatile (
        "syscall\n"
        : "=a" (result)
        : "0" (4), "D" (file_descriptor), "S" (&file_info)
        : "memory"
    );

    if (result != 0) {
        uint64_t file_size = file_info.st_size;

        // Read and print the content based on the file size
        char *buffer = (char *)malloc(file_size + 1);
        if (buffer == NULL) {
            perror("malloc error");
            return 1;
        }

        ssize_t bytes_read = read(file_descriptor, buffer, file_size);
        if (bytes_read == -1) {
            perror("read error");
            free(buffer);
            return 1;
        }
        buffer[file_size] = '\0';
        printf("File size: %lld bytes\n", (long long)file_size);
        printf("File content:\n%s\n", buffer);
        free(buffer);
    } else {
        perror("stat error");
        return 1;
    }

    return 0;
}
