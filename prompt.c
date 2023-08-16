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
    if (strncmp(input, "cd", 2) == 0) {
      char *dir = strtok(input + 3, " ");
      if (dir == NULL) {
	dir = getenv("HOME");
      } else if (strcmp(dir, "-") == 0) {
	dir = getenv("OLDPWD");
	printf("%s\n", dir);
      }

      char *oldpwd = getcwd(NULL, 0);
      if (chdir(dir) != 0) {
	perror("chdir");
      } else {
	setenv("OLDPWD", oldpwd, 1);
	free(oldpwd);
	char *newpwd = getcwd(NULL, 0);
	setenv("PWD", newpwd, 1);
	free(newpwd);
      }
      continue;
    }

  }

  return 0;
}
