#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT ":) "
#define MAX_ARGS 10

int count_tokens(char *input) {

}

void parse_input(char *input, char *args[]) {

}

int main(void)
{
    char input[100];
    char *args[MAX_ARGS + 1];
    char *path = "/bin:/usr/bin";
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

	if (strncmp(input, "exit", 4) == 0) {
	  int exit_status = 0;
	  if (strlen(input) > 4) {
                exit_status = atoi(input + 5);
		}
            printf("Exiting the shell with status %d\n", exit_status);
            exit(exit_status);
        }

	if (strcmp(input, "env") == 0) {
	  continue;
        }

	int arg_count = count_tokens(input);
        if (arg_count == 0) {
            continue;
        }

        parse_input(input, args);

        int found = 0;
        char full_path[100];
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

	
        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {

	  execv(full_path, args);

	  perror("execv");
            exit(EXIT_FAILURE);
        } else {
	  waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}
