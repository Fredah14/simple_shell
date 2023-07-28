#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * input_buf - buffers the chained commands
 * @info: struct address
 * @buf: the buffer address
 * @len: len variable address
 *
 * Return: the read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rb = 0;
	size_t len_k = 0;

if (!*len)
{
free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rb = getline(buf, &len_k, stdin);
#else
		rb = _getline(info, buf, &len_k);
#endif
		if (rb > 0)
		{
			if ((*buf)[rb - 1] == '\n')
			{
				(*buf)[rb - 1] = '\0';
				rb--;
			}
			info->linecount_flag = 1;
rem_comments(*buf);
build_history_list(info, *buf, info->histcount++);
{
				*len = rb;
				info->cmd_buf = buf;
			}
		}
	}
	return (rb);
}

/**
 * get_input - gets line minus the newline
 * @info: the struct parameter
 *
 * Return: the read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t j, l, len;
	ssize_t rb = 0;
	char **buf_k = &(info->arg), *k;

	_putchar(BUF_FLUSH);
	rb = input_buf(info, &buf, &len);
	if (rb == -1)
		return (-1);
	if (len)
	{
		l = j;
		k = buf + j;

		check_chain(info, buf, &l, j, len);
		while (l < len)
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}

		j = l + 1;
		if (j >= len)
		{
			j = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_k = k;
		return (_strlen(k));
	}

	*buf_k = buf;
	return (rb);
}

/**
 * read_buf - reads a buffer
 * @info: the struct address
 * @buf: the buffer address
 * @i: the size
 *
 * Return: rb
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rb = 0;

	if (*i)
		return (0);
	rb = read(info->readfd, buf, READ_BUF_SIZE);
	if (rb >= 0)
		*i = rb;
	return (rb);
}

/**
 * _getline - gets next line of the input from STDIN
 * @info: the struct parameter
 * @ptr: pointer to buffer address
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t m;
	ssize_t rb = 0, s = 0;
	char *k = NULL, *new_k = NULL, *c;

	k = *ptr;
	if (k && length)
		s = *length;
	if (j == len)
		j = len = 0;

	rb = read_buf(info, buf, &len);
	if (rb == -1 || (rb == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	m = c ? 1 + (unsigned int)(c - buf) : len;
	new_k = _realloc(k, s, s ? s + m : m + 1);
	if (!new_k)
		return (k ? free(k), -1 : -1);

	if (s)
		_strncat(new_k, buf + j, m - j);
	else
		_strncpy(new_k, buf + j, m - j + 1);

	s += m - j;
	j = m;
	k = new_k;

	if (length)
		*length = s;
	*ptr = k;
	return (s);
}

/**
 * sigintHandler - blocks the ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
