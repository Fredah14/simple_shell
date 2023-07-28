#include "shell.h"

/**
 * get_envi - returns the copy of string array environ
 * @info: contain potential arguments to maintain constant func prototy
 *
 * Return: Always 0
 */
char **get_envi(info_t *info)
{
	if (!info->envi || info->env_changed)
	{
		info->envi = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->envi);
}

/**
 * _unsetenv - Removes environment variable
 * @info: contain potential arguments to maintain constant func prototy
 * @var: string env variable
 *
 *  Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nodes = info->env;
	size_t j = 0;
	char *k;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		k = starts_with(nodes->str, var);
		if (k && *k == '=')
		{
			info->env_changed = delete_nodes_at_index(&(info->env), j);
			j = 0;
			nodes = info->env;
			continue;
		}
		nodes = nodes->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - initialize new environment variable or modifies existing
 * @info: contain potential arguments to maintain constant func prototy
 * @var: environment variable string
 * @val: value environment variable string
 *
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *val)
{
	char *buffs = NULL;
	list_t *nodes;
	char *k;

	if (!var || !val)
		return (0);

	buffs = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buffs)
		return (1);
	_strcpy(buffs, var);
	_strcat(buffs, "=");
	_strcat(buffs, val);
	nodes = info->env;
	while (nodes)
	{
		k = starts_with(nodes->str, var);
		if (k && *k == '=')
		{
			free(nodes->str);
			nodes->str = buffs;
			info->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	add_nodes_end(&(info->env), buffs, 0);
	free(buffs);
	info->env_changed = 1;
	return (0);
}
