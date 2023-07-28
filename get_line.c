#include "shell.h"

/**
 * input_buffs - buffers the chained commands
 * @info: the struct address
 * @buffs: the buffer addresss
 * @len: len variable addresss
 *
 */
ssize_t input_buffs(info_t *info, char **buffs, size_t *len)
{
	ssize_t re = 0;
	size_t len_k = 0;

	if (!*len)
	{
		free(*buffs);
		*buffs = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		re = getline(buffs, &len_k, stdin);
#else
		re = _getline(info, buffs, &len_k);
#endif
		if (re > 0)
		{
			if ((*buffs)[re - 1] == '\n')
			{
				(*buffs)[re - 1] = '\0';
				re--;
			}
			info->linecount_flag = 1;
			rem_comments(*buffs);
			build_history_list(info, *buffs, info->histcount++);

			{
				*len = re;
				info->cmd_buf = buffs;
			}
		}
	}
	return (re);
}

/**
 * get_input - gets line minus the newline
 * @info: the struct address
 *
 * Return: the bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffs;
	static size_t j, l, len;
	ssize_t re = 0;
	char **buffs_k = &(info->arg), *k;

	_putchar(BUF_FLUSH);
	re = input_buffs(info, &buffs, &len);
	if (re == -1)
		return (-1);
	if (len)
	{
		l = j;
		k = buffs + j;

		check_chain(info, buffs, &l, j, len);
		while (l < len)
		{
			if (is_chain(info, buffs, &l))
				break;
			l++;
		}

		j = l + 1;
		if (i >= len)
		  j = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffs_k = k;
		return (_strlen(k));
		*buffs_k = buffs;
	return (re);
}

/**
 * read_buf - reads a buffer
 * @info: the struct address
 * @buf: the buffer address
 * @j: the size
 *
 * Return: re
 */
ssize_t read_buf(info_t *info, char *buffs, size_t *j)
{
	ssize_t re = 0;

	if (*j)
		return (0);
	re = read(info->readfd, buffs, READ_BUF_SIZE);
	if (re >= 0)
		*j = re;
	return (re);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: the struct address
 * @ptr: pointer to buffer address
 * @length: size of pointer
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffs[READ_BUF_SIZE];
	static size_t j, len;
	size_t m;
	ssize_t re = 0, s = 0;
	char *k = NULL, *new_k = NULL, *c;

	k = *ptr;
	if (k && length)
		s = *length;
	if (j == len)
		j = len = 0;

	re = read_buf(info, buffs, &len);
	if (re == -1 || (re == 0 && len == 0))
		return (-1);

	c = _strchr(buffs + j, '\n');
	m = c ? 1 + (unsigned int)(c - buffs) : len;
	new_k = _realloc(k, s, s ? s + m : m + 1);
	if (!new_k)
		return (k ? free(k), -1 : -1);

	if (s)
		_strncat(new_k, buffs + j, m - j);
	else
		_strncpy(new_k, buffs + j, m - j + 1);

	s += m - j;
	j = m;
	k = new_k;

	if (length)
		*length = s;
	*ptr = k;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number parameter
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
