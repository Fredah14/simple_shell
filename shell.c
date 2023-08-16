#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

int main(void)
{
    char command[100];
    char *args[2];
    pid_t child_pid;
    int status;

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {

            printf("\n");
            break;
        }

        command[strlen(command) - 1] = '\0';

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {

            args[0] = command;
            args[1] = NULL;

            execve(command, args, NULL);

            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}
