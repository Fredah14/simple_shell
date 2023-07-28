#include "shell.h"

/**
 * _history - displays history list one command by line, preceded
 * with line numbers, starting from 0.
 * @info: potential arguments used to maintain constant func prototype.
 *
 * Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to a string
 * @info: potential arguments used to maintain constant func prototype.
 * @str: alias string
 *
 * Return: Always 0, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *k, l;
	int ret;

	k = _strchr(str, '=');
	if (!k)
		return (1);
	l = *k;
	*k = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*k = l;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: potential arguments used to maintain constant func prototype.
 * @str: the string alias
 *
 * Return: Always 0, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *k;

	k = _strchr(str, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nodes: the alias node
 *
 * Return: Always 0, 1 on error
 */
int print_alias(list_t *nodes)
{
	char *k = NULL, *a = NULL;

	if (nodes)
	{
		k = _strchr(nodes->str, '=');
		for (a = nodes->str; a <= k; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(k + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias _prompt
 * @info: potential arguments used to maintain constant func prototype.
 *
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *k = NULL;
	list_t *nodes = NULL;

	if (info->argc == 1)
	{
		nodes = info->alias;
		while (nodes)
		{
			print_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		k = _strchr(info->argv[i], '=');
		if (k)
			set_alias(info, info->argv[i]);
		else
			print_alias(nodes_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
