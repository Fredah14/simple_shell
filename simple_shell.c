#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define PROMPT ":) "

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        ssize_t bytes_read = getline(&input, &input_size, stdin);

        if (bytes_read == -1) {
            if (feof(stdin)) {
                printf("\n");
                free(input);
                break;

		}
	    perror("getline");
            free(input);
            exit(EXIT_FAILURE);
        }

        input[bytes_read - 1] = '\0';

	pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            free(input);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
          char *args[] = {input, NULL};
            execve(input, args, NULL);
            perror(input);
            free(input);
            exit(EXIT_FAILURE);
        } else {
	  waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
