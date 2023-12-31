#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT ":) "
#define MAX_ARGS 10

int count_tokens(char *input) {
  // Same as before...
}

void parse_input(char *input, char *args[]) {
  // Same as before...
}

int main(void)
{
  char input[100];  // Assuming commands are limited to 100 characters
  char *args[MAX_ARGS + 1];  // +1 for the NULL terminator
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
    if (strncmp(input, "exit", 4) == 0) {
      int exit_status = 0;
      if (strlen(input) > 4) {
	exit_status = atoi(input + 5);  // Skip "exit " and parse status
      }
      printf("Exiting the shell with status %d\n", exit_status);
      exit(exit_status);
    }

    // Handle the setenv built-in command
    if (strncmp(input, "setenv", 6) == 0) {
      char *var = strtok(input + 7, " ");
      char *val = strtok(NULL, " ");
      if (var != NULL && val != NULL) {
	if (setenv(var, val, 1) == -1) {
	  perror("setenv");
	}
      } else {
	fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
      }
      continue;
    }

    // Handle the unsetenv built-in command
    if (strncmp(input, "unsetenv", 8) == 0) {
      char *var = strtok(input + 9, " ");
      if (var != NULL) {
	if (unsetenv(var) == -1) {
	  perror("unsetenv");
	}
      } else {
	fprintf(stderr, "Usage: unsetenv VARIABLE\n");
      }
      continue;
    }

    // Handle the env built-in command
    if (strcmp(input, "env") == 0) {
      // Same as before...
      continue;
    }

    // Parse the input into arguments
    int arg_count = count_tokens(input);
    if (arg_count == 0) {
      // No command entered, show prompt again
      continue;
    }

    parse_input(input, args);

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
