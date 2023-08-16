#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT ":) "
#define MAX_ARGS 10

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
    if (strcmp(input, "exit") == 0) {
      printf("Exiting the shell\n");
      break;
      }
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
    int found = 0;
    char full_path[100];
    char *path_token = strtok(path, ":");
    while (path_token != NULL) {
      sprintf(full_path, sizeof(full_path), "%s/%s", path_token, args[0]);
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
