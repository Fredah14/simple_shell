#include "shell.h"
/**
 * _get_path - get variable PATH.
 * @env: variable
 * Return: value of PATH.
 */

char *_get_path(char **env)
{
size_t content = 0, variable = 0, count = 5;
char *path = NULL;
for (content = 0; _strncmp(env[content], "PATH=", 5); content++)
;
if (env[content] == NULL)
return (NULL);
for (count = 5; env[content][variable; variable++, count++)
;
path = malloc(sizeof(char) * (count + 1));
if (path == NULL)
return (NULL);
for (variable = 5, count = 0; env[content][variable]; variable++, count++)
path[count] = env[content][variable];
path[count] = '\0';
return (path);
}
