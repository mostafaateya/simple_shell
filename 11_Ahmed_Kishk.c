#include "simple_shell.h"

/**
 * **string_split_2 - splits a string into two words
 * @ss: string input needed
 * @s: delimeter string
 * Return: pointer to array of strings
 */

char **string_split_2(char *ss, char *s)
{
	int x, y, z, m, words_count = 0;
	char **c;

	if (ss == NULL || ss[0] == 0)
		return (NULL);
	if (!s)
		s = " ";
	for (x = 0; ss[x] != '\0'; x++)
		if (!_isdeterm(ss[x], s) && (_isdeterm(ss[x + 1], s) || !ss[x + 1]))
			words_count++;
	if (words_count == 0)
		return (NULL);
	c = malloc((1 + words_count) * sizeof(char *));
	if (!c)
		return (NULL);
	for (x = 0, y = 0; y < words_count; y++)
	{
		while (_isdeterm(ss[x], s))
			x++;
		z = 0;
		while (!_isdeterm(ss[x + z], s) && ss[x + z])
			z++;
		c[y] = malloc((z + 1) * sizeof(char));
		if (!c[y])
		{
			for (z = 0; z < y; z++)
				free(c[z]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			c[y][m] = ss[x++];
		c[y][m] = 0;
	}
	c[y] = NULL;
	return (c);
}

/**
 * **string_split - splits a string into words
 * @ss: string input needed
 * @s: delimeter string
 * Return: pointer to an array of strings
 */

char **string_split(char *ss, char s)
{
	int x, y, z, m, words_count = 0;
	char **c;

	if (ss == NULL || ss[0] == 0)
		return (NULL);
	for (x = 0; ss[x] != '\0'; x++)
		if ((ss[x] != s && ss[x + 1] == s) ||
				(ss[x] != s && !ss[x + 1]) || ss[x + 1] == s)
			words_count++;
	if (words_count == 0)
		return (NULL);
	c = malloc((1 + words_count) * sizeof(char *));
	if (!c)
		return (NULL);
	for (x = 0, y = 0; y < words_count; y++)
	{
		while (ss[x] == s && ss[x] != s)
			x++;
		z = 0;
		while (ss[x + z] != s && ss[x + z] && ss[x + z] != s)
			z++;
		c[y] = malloc((z + 1) * sizeof(char));
		if (!c[y])
		{
			for (z = 0; z < y; z++)
				free(c[z]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			c[y][m] = ss[x++];
		c[y][m] = 0;
	}
	c[y] = NULL;
	return (c);
}
