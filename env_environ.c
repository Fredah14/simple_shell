#include "shell.h"

/**
 * _env - prints the current environment
 * @info: contains potential arguments to main constant fun prototype.
 *
 * Return: Always 0
 */
int _env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: contains potential arguments to main constant fun prototype.
 * @name: variable name
 *
 * Return: the value of an dnv variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *nodes = info->env;
	char *p;

	while (nodes)
	{
		p = starts_with(nodes->str, name);
		if (p && *p)
			return (p);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initialize a new environment variable,
 *             or modify an existing one
 * @info: contains potential arguments to main constant fun prototype.
 *
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect arguements number\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: contains potential arguments to main constant fun prototype.
 *
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: contains potential arguments to main constant fun prototype.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *nodes = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nodes_end(&nodes, environ[i], 0);
	info->env = nodes;
	return (0);
}
