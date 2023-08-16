#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "$ "

extern char **environ;  // Variable that contains the environment

int main(void)
{
    char input[100];  // Assuming commands are limited to 100 characters
    char *args[2];  // For built-in commands with 2 arguments
    char *path = "/bin:/usr/bin";  // Example PATH, you can modify it
    pid_t child_pid;
    int status;

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove trailing newline
        input[strlen(input) - 1] = '\0';

        // Handle the exit built-in command
        if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell\n");
            break;
        }

        // Handle the env built-in command
        if (strcmp(input, "env") == 0) {
            char **env_ptr = environ;
            while (*env_ptr != NULL) {
                printf("%s\n", *env_ptr);
                env_ptr++;
            }
            continue;
        }

        // Split the input into arguments
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < 2) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;  // Null-terminate the arguments array

        if (arg_count == 0) {
            // No command entered, show prompt again
            continue;
        }

        // Check if the command exists in the PATH
        int found = 0;
        char full_path[100];  // Assuming path length is limited to 100 characters
        char *path_token = strtok(path, ":");
        while (path_token != NULL) {
            snprintf(full_path, sizeof(full_path), "%s/%s", path_token, args[0]);
            if (access(full_path, X_OK) == 0) {
                found = 1;
                break;
            }
            path_token = strtok(NULL, ":");
        }

        if (!found) {
            printf("%s: command not found\n", args[0]);
            continue;
        }

        // Fork a child process
        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            execv(full_path, args);

            // If execv fails
            perror("execv");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}
