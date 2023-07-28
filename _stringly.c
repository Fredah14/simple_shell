#include "shell.h"

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be used
 *
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, l;
	char *s = dest;

	j = 0;
	l = 0;
	while (dest[j] != '\0')
		j++;
	while (src[l] != '\0' && l < n)
	{
		dest[j] = src[l];
		j++;
		l++;
	}
	if (l < n)
		dest[j] = '\0';
	return (s);
}

/**
 **_strncpy - copies a string
 *@dest: destination string to copy to
 *@src: source string
 *@n: amount of characters to copy
 *
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, l;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		l = j;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (s);
}

/**
 **_strchr - locates a char in a string
 *@s: string to parse
 *@c: character to locate
 *
 *Return: string
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
