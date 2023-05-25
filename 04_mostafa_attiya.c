#include "simple_shell.h"

/**
 * character_print - writes a character a into a file
 * @a: printed character
 * @write_flag: a flag to write
 * Return: 1 on Success
 */

int character_print(char a, int write_flag)
{
	static int q;
	static char write_size[BUFFER_FOR_WRITE_FUNCTION];

	if (a == BUFFER_CLEARING || q >= BUFFER_FOR_WRITE_FUNCTION)
	{
		write(write_flag, write_size, q);
		q = 0;
	}
	if (a != BUFFER_CLEARING)
		write_size[q++] = a;
	return (1);
}

/**
 * string_print - prints an input string
 * @ss: string to be printed
 * @write_flag: a flag to write
 * Return: the string to be printed
 */

int string_print(char *ss, int write_flag)
{
	int v = 0;

	if (!ss)
		return (0);
	while (*ss)
		v += character_print(*ss++, write_flag);
	return (v);
}

/**
 * error_string_print - prints an input error string
 * @ss: string to be printed
 * Return: void
 */

void error_string_print(char *ss)
{
	int l;

	if (!ss)
		return;
	for (l = 0; ss[l] != '\0'; l++)
		error_putchar(ss[l]);
}

/**
 * error_putchar - writes a character a to stderr
 * @a: character to be printed
 * Return: 1 on Success
 */

int error_putchar(char a)
{
	static int q;
	static char write_size[BUFFER_FOR_WRITE_FUNCTION];

	if (a == BUFFER_CLEARING || q >= BUFFER_FOR_WRITE_FUNCTION)
	{
		write(2, write_size, q);
		q = 0;
	}
	if (a != BUFFER_CLEARING)
		write_size[q++] = a;
	return (1);
}
