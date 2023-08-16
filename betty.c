#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

void display_prompt(void)
{
    printf("($) ");
}

char *read_command(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

int execute_command(char *command)
{
    pid_t pid;
    int status;

    command[strcspn(command, "\n")] = '\0'; // Remove newline
    pid = fork();

    if (pid == 0) {
        // Child process
        if (execlp(command, command, NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
    return 1;
}

int main(void)
{
    char *command;
    int status = 1;

    while (status) {
        display_prompt();
        command = read_command();
        status = execute_command(command);
        free(command);
    }
    return 0;
}
