#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int execute_command(char *cmd) {
    char *args[] = {"/bin/sh", "-c", cmd, NULL};

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        execve("/bin/sh", args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            // The child process exited
            int exit_status = WEXITSTATUS(status);

            if (exit_status == 0)
                return (0);
            else
                printf("\e[1;32mCommand '%s' failed with exit code %d\n", cmd, exit_status);
        }
    }
    return (0);
}

int main() {
    // Example with &&
    //execute_command("ls");
    if (!execute_command("ls") && !execute_command("echo 'Second command after ls'"))
        return (0);
    printf("error\n");
    // Example with ||
    //execute_command("ls_nonexistent");
    //execute_command("echo 'Second command after failure'");

    return 0;
}
