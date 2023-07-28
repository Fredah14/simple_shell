#include "shell.h"

/**
 * _erroratoi - converts string to an int
 * @s: string to be converted
 *
 * Return: 0 Always, otherwise -1 on error
 */
int _erroratoi(char *s)
{
	int j = 0;
	unsigned long int results = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			results *= 10;
			results += (s[j] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_error - prints error message
 * @info: contains potential arguments to main constatnt func prototyp
 * @errstr: contains specified error type string
 * Return: 0 Always, otherwise -1 on error
 */
void print_error(info_t *info, char *errstr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_d - prints a decimal number
 * @input: the input to be printed
 * @fd: filedescriptor to write to
 *
 * Return: number of characters
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + curr / j);
			count++;
		}
		curr %= j;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * convert_number - converts numbers
 * @num: number to be converted
 * @base: the base
 * @flags: the argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long nb = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		nb = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[nb % base];
		nb /= base;
	} while (nb != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_comments - replaces first instance of '#' with '\0'
 * @buffs: address of string to modify
 *
 * Return: Always 0
 */
void rem_comments(char *buffs)
{
	int j;

	for (j = 0; buffs[j] != '\0'; j++)
		if (buffs[j] == '#' && (!j || buffs[j - 1] == ' '))
		{
			buffs[j] = '\0';
			break;
		}
}
