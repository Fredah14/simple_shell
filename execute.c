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

void execute_command(char *input) {
    char *commands[MAX_ARGS];
    char *command;
    int command_count = 0;

    command = strtok(input, ";");
    while (command != NULL) {
        commands[command_count++] = command;
        command = strtok(NULL, ";");
    }

    for (int i = 0; i < command_count; i++) {
        char *args[MAX_ARGS + 1];
        char *command = commands[i];


    }
}

int main(void)
{
    char input[100];

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
        
            printf("\n");
            break;
        }

	input[strlen(input) - 1] = '\0';

        execute_command(input);
    }

    return 0;
}
