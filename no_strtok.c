#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT ":) "
#define MAX_ARGS 10

int count_tokens(char *input) {
    int count = 0;
    char *ptr = input;
    int in_token = 0;

    while (*ptr != '\0') {
        if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
            if (in_token) {
                in_token = 0;
            }
        } else {
            if (!in_token) {
                in_token = 1;
                count++;
            }
        }
        ptr++;
    }

    return count;
}

void parse_input(char *input, char *args[]) {
    int arg_count = 0;
    char *ptr = input;
    int in_token = 0;

    while (*ptr != '\0') {
        if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') {
            if (in_token) {
                in_token = 0;
                *ptr = '\0';
            }
        } else {
            if (!in_token) {
                in_token = 1;
                args[arg_count++] = ptr;
            }
        }
        ptr++;
    }
    args[arg_count] = NULL;
}

int main(void)
{
    char input[100];
    char *args[MAX_ARGS + 1]
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

	if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell\n");
            break;
        }

	
        if (strcmp(input, "env") == 0) {
            char **env_ptr = environ;
            while (*env_ptr != NULL) {
                printf("%s\n", *env_ptr);
                env_ptr++;
            }
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
