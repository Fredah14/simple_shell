#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_ARGS 10

int main(void)
{
    char input[100];
    char *args[MAX_ARGS + 1];
    pid_t child_pid;
    int status;

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strlen(input) - 1] = '\0';
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < MAX_ARGS) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        if (arg_count == 0) {
            continue;
        }

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            execvp(args[0], args);

            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
	  waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}
