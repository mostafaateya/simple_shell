#include "simple_shell.h"

/**
 * ss_alias - runs alias command
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_alias(sample_type *func_data)
{
	int z = 0;
	char *c = NULL;
	linked_list *x = NULL;

	if (func_data->argc == 1)
	{
		x = func_data->alias;
		while (x)
		{
			print_alias(x);
			x = x->nxt;
		}
		return (0);
	}
	for (z = 1; func_data->argv[z]; z++)
	{
		c = _strchr(func_data->argv[z], '=');
		if (c)
			add_alias(func_data, func_data->argv[z]);
		else
			print_alias(get_node_prefix(func_data->alias, func_data->argv[z], '='));
	}
	return (0);
}

/**
 * print_alias - prints an alias string
 * @x: alias node
 * Return: 0 on Success
 */

int print_alias(linked_list *x)
{
	char *ptr = NULL, *c = NULL;

	if (x)
	{
		ptr = _strchr(x->ns, '=');
		for (c = x->ns; c <= ptr; c++)
		_putchar(*c);
		_putchar('/');
		_puts(ptr + 1);
		_puts("\n");
		return (0);
	}
	return (1);
}

/**
 * add_alias - adds alias string
 * @func_data: structure containing a data model
 * @s_a: string alias
 * Return: 0 on Success
 */

int add_alias(sample_type *func_data, char *s_a)
{
	char *ptr;

	ptr = _strchr(s_a, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (remove_alias(func_data, s_a));
	remove_alias(func_data, s_a);
	return (add_node_end(&(func_data->alias), s_a, 0) == NULL);
}

/**
 * remove_alias - removes alias string
 * @func_data: structure containing a data model
 * @s_a: string alias
 * Return: 0 on Success
 */

int remove_alias(sample_type *func_data, char *s_a)
{
	char *ptr, c;
	int output;

	ptr = _strchr(s_a, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	output = remove_node_index(&(func_data->alias),
			node_index(func_data->alias, get_node_prefix(func_data->alias, s_a, -1)));
	*ptr = c;
	return (output);
}

/**
 * ss_history - runs history linked list
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_history(sample_type *func_data)
{
	print_list(func_data->history);
	return (0);
}
