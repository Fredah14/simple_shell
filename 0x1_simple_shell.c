#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: character to check
 * @delim: delimeter str
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for the alphabetic character
 *@c: character to input
 *Return: 1 if c is alphabetic, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - convert a string to an integer
 *@s: the string to convert
 *Return: 0 if no numbers in string, cotherwise converted number
 */

int _atoi(char *s)
{
	int i, signs = 1, flags = 0, output;
	unsigned int results = 0;

	for (i = 0;  s[i] != '\0' && flags != 2; i++)
	{
		if (s[i] == '-')
			signs *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flags = 1;
			results *= 10;
			results += (s[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		output = -results;
	else
		output = results;

	return (output);
}
