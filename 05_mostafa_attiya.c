#include "simple_shell.h"

/**
 *  _strncpy - copies a string
 *  @dest: destination string
 *  @src: source string
 *  @n: number of characters to be copied
 *  Return: destination string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int m, k;
	char *c = dest;

	for (m = 0; src[m] != '\0' && m < n - 1; m++)
		dest[m] = src[m];
	if (m < n)
	{
		for (k = m; k < n; k++)
			dest[k] = '\0';
	}
	return (c);
}

/**
 * _strncat - concatenates two string
 * @dest: destination string
 * @src: source string
 * @n: number of characters to be concatenated
 * Return: destination string
 */

char *_strncat(char *dest, char *src, int n)
{
	int m, k;
	char *c = dest;

	for (m = 0; dest[m] != '\0'; m++)
		;
	for (k = 0; src[n] != '\0' && k < n; k++)
	{
		dest[m] = src[k];
		m++;
	}
	if (k < n)
		dest[m] = '\0';
	return (c);
}

/**
 * _strchr - gets a character into a string
 * @ss: string input needed
 * @a: a character to be looked for
 * Return: pointer to a character
 */

char *_strchr(char *ss, char a)
{
	do {
		if (*ss == a)
			return (ss);
	} while (*ss++ != '\0');
	return (NULL);
}
