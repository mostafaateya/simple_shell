#include "simple_shell.h"

/**
 * ctrl_c - blocks ctrl-c
 * @n: first needed input
 * Return: void
 */

void ctrl_c(__attribute__((unused))int n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_CLEARING);
}

/**
 * chained_buffers - buffers chained commands
 * @func_data: structure containing a data model
 * @input_buffer: buffer input needed
 * @input_length: length of a buffer
 * Return: reading bytes
 */

ssize_t chained_buffers(sample_type *func_data,
		char **input_buffer, size_t *input_length)
{
	ssize_t i = 0;
	size_t len_p = 0;

	if (!*input_length)
	{
		free(*input_buffer);
		*input_buffer = NULL;
		signal(SIGINT, ctrl_c);
#if GETLINE_USING
		i = getline(input_buffer, &len_p, stdin);
#else
		i = ss_getline(func_data, input_buffer, &len_p);
#endif
		if (i > 0)
		{
			if ((*input_buffer)[i - 1] == '\n')
			{
				(*input_buffer)[i - 1] = '\0';
				i--;
			}
			func_data->counter_flag = 1;
			remove_comments(*input_buffer);
			linked_list_history(func_data, *input_buffer,
					func_data->history_counter_row++);
			if (_strchr(*input_buffer, ';'))
			{
				*input_length = i;
				func_data->chainning_buffer = input_buffer;
			}
		}
	}
	return (i);
}

/**
 * read_chained_buffers - reads a buffer
 * @func_data: structure containing a data model
 * @input_buffer: buffer input needed
 * @input_length: length of buffer
 * Return: i
 */

ssize_t read_chained_buffers(sample_type *func_data,
		char *input_buffer, size_t *input_length)
{
	ssize_t i = 0;

	if (*input_length)
		return (0);
	i = read(func_data->fd_read, input_buffer, BUFFER_FOR_READ_FUNCTION);
	if (i >= 0)
		*input_length = i;
	return (i);
}

/**
 * input_get_line - gets a line
 * @func_data: structure containing a data model
 * Return: reading bytes
 */

ssize_t input_get_line(sample_type *func_data)
{
	static char *c;
	static size_t m, n, length;
	ssize_t i = 0;
	char **p = &(func_data->s_cmd), *a;

	_putchar(BUFFER_CLEARING);
	i = chained_buffers(func_data, &c, &length);
	if (i == -1)
		return (-1);
	if (length)
	{
		n = m;
		a = c + m;
		chaining_continue(func_data, c, &n, m, length);
		while (n < length)
		{
			if (chaining_delimeter(func_data, c, &n))
				break;
			n++;
		}
		m = n + 1;
		if (m >= length)
		{
			m = length = 0;
			func_data->mode_command = NORMAL_MODE_COMMAND;
		}
		*p = a;
		return (string_length(a));
	}
	*p = c;
	return (i);
}

/**
 * ss_getline - gets the next line
 * @func_data: structure containing a data model
 * @ptr: pointer to character
 * @length: length of buffer
 * Return: output
 */

int ss_getline(sample_type *func_data, char **ptr, size_t *length)
{
	static char read_buffer[BUFFER_FOR_READ_FUNCTION];
	static size_t i, len;
	size_t z;
	ssize_t r = 0, output = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		output = *length;
	if (i == len)
		i = len = 0;
	r = read_chained_buffers(func_data, read_buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(read_buffer + i, '\n');
	z = c ? 1 + (unsigned int)(c - read_buffer) : len;
	new_p = _realloc(p, output, output ? output + z : z + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (output)
		_strncat(new_p, read_buffer + i, z - i);
	else
		_strncpy(new_p, read_buffer + i, z - i + 1);
	output += z - i;
	i = z;
	p = new_p;
	if (length)
		*length = output;
	*ptr = p;
	return (output);
}
