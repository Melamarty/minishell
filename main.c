#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd; // file descriptor
    int stdout_copy; // copy of original stdout

    // Open a file for writing (creates the file if it doesn't exist, truncates it to zero length if it exists)
    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Duplicate stdout to save a copy
    stdout_copy = dup(STDOUT_FILENO);

    // Redirect stdout to the file descriptor and tee to the terminal
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Error duplicating file descriptor");
        exit(EXIT_FAILURE);
    }

    // Use tee to duplicate the output to the terminal
    if (dup2(fd, STDERR_FILENO) == -1) {
        perror("Error duplicating file descriptor");
        exit(EXIT_FAILURE);
    }

    // Close the original file descriptor (it's duplicated to STDOUT_FILENO now)
    close(fd);

    // Now, anything written to stdout will go to the file "output.txt" and the terminal
    printf("This will be written to the file and printed to the terminal.\n");

    // Restore stdout to the original file descriptor (usually the terminal)
    if (dup2(stdout_copy, STDOUT_FILENO) == -1) {
        perror("Error restoring file descriptor");
        exit(EXIT_FAILURE);
    }

    // This will be printed to the terminal again
    printf("This will be printed to the terminal.\n");

    // Close the duplicated stdout_copy file descriptor
    close(stdout_copy);

    return 0;
}
