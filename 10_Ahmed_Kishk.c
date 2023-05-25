#include "simple_shell.h"

/**
 * string_copy - copies a string
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */

char *string_copy(char *dest, char *src)
{
	int t = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = 0;
	return (dest);
}

/**
 * string_duplicate - duplicates string
 * @ss: string input needed
 * Return: pointer to string
 */

char *string_duplicate(const char *ss)
{
	int length = 0;
	char *output;

	if (ss == NULL)
		return (NULL);
	while (*ss++)
		length++;
	output = malloc(sizeof(char) * (length + 1));
	if (!output)
		return (NULL);
	for (length++; length--;)
		output[length] = *--ss;
	return (output);
}

/**
 * _puts - prints an input string
 * @ss: string input needed
 * Return: void
 */

void _puts(char *ss)
{
	int z = 0;

	if (!ss)
		return;
	while (ss[z] != '\0')
	{
		_putchar(ss[z]);
		z++;
	}
}

/**
 * _putchar - prints a character
 * @c: character input needed
 * Return: 1 on Success
 */

int _putchar(char c)
{
	static int x;
	static char write_buffer[BUFFER_FOR_WRITE_FUNCTION];

	if (c == BUFFER_CLEARING || x >= BUFFER_FOR_WRITE_FUNCTION)
	{
		write(1, write_buffer, x);
		x = 0;
	}
	if (c != BUFFER_CLEARING)
		write_buffer[x++] = c;
	return (1);
}
