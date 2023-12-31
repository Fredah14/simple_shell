#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_INPUT 1024

char *my_getline(void)
{
    static char buffer[MAX_INPUT];
    static int buffer_index = 0;
    static int buffer_size = 0;

    char *line = NULL;
    int line_length = 0;
    int newline_found = 0;

    while (!newline_found) {
        if (buffer_index >= buffer_size) {
            buffer_size = read(STDIN_FILENO, buffer, MAX_INPUT);
            if (buffer_size <= 0) {
                return NULL;
            }
            buffer_index = 0;
        }

        char current_char = buffer[buffer_index++];
        if (current_char == '\n' || current_char == '\0') {
            newline_found = 1;
        } else {
            if (line_length == 0) {
                line = (char *)malloc(MAX_INPUT);
                if (line == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
            }
            line[line_length++] = current_char;
        }
    }

    if (line != NULL) {
        line[line_length] = '\0';
    }

    return line;
}

int main(void)
{
    char *input;
    char *args[10];
    pid_t child_pid;
    int status;

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        input = my_getline();
        if (input == NULL) {
	  printf("\n");
            break;
        }

        free(input);
    }

    return 0;
}
