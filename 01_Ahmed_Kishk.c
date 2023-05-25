#include "simple_shell.h"

/**
 * _atoi - converts a string to an integer
 * @digit: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *digit)
{
	int z, negative = 1, i = 0, output;
	unsigned int out = 0;

	for (z = 0; digit[z] != '\0' && i != 2; z++)
	{
		if (digit[z] == '-')
			negative *= -1;
		if (digit[z] >= '0' && digit[z] <= '9')
		{
			i = 1;
			out *= 10;
			out += (digit[z] - '0');
		}
		else if (i == 1)
			i = 2;
	}
	if (negative == -1)
		output = -out;
	else
		output = out;
	return (output);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _isdeterm - checks if character is a specified
 * @a: the char to check
 * @determined: the specified string
 * Return: 1 if true, 0 if false
 */

int _isdeterm(char a, char *determined)
{
	while (*determined)
		if (*determined++ == a)
			return (1);
	return (0);
}

/**
 * play - returns true if shell is play mode
 * @func_data: struct address
 * Return: 1 if play mode, 0 otherwise
 */

int play(sample_type *func_data)
{
	return (isatty(STDIN_FILENO) && func_data->fd_read <= 2);
}
