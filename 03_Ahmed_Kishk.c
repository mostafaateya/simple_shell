#include "simple_shell.h"

/**
 * chaining_delimeter - checks current character a chain delimeter
 * @func_data: structure containing a data model
 * @c: character buffer
 * @p: pointer to current character
 * Return: 1 on Success
 */

int chaining_delimeter(sample_type *func_data, char *c, size_t *p)
{
	size_t a = *p;

	if (c[a] == '|' && c[a + 1] == '|')
	{
		c[a] = 0;
		a++;
		func_data->mode_command = OR_MODE_COMMAND;
	}
	else if (c[a] == '&' && c[a + 1] == '&')
	{
		c[a] = 0;
		a++;
		func_data->mode_command = AND_MODE_COMMAND;
	}
	else if (c[a] == ';')
	{
		c[a] = 0;
		func_data->mode_command = END_MODE_COMMAND;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * chaining_continue - checks chaining conytinuaty
 * @func_data: structure containing a data model
 * @c: character buffer
 * @p: pointer to character
 * @n: starting position
 * @length: length of c
 * Return: void
 */

void chaining_continue(sample_type *func_data, char *c, size_t *p,
		size_t n, size_t length)
{
	size_t a = *p;

	if (func_data->mode_command == AND_MODE_COMMAND)
	{
		if (func_data->feedback)
		{
			c[n] = 0;
			a = length;
		}
	}
	if (func_data->mode_command == OR_MODE_COMMAND)
	{
		if (!func_data->feedback)
		{
			c[n] = 0;
			a = length;
		}
	}
	*p = a;
}

/**
 * change_ss_alias - changes alias string
 * @func_data: structure containing a data model
 * Return: 1 on Success
 */

int change_ss_alias(sample_type *func_data)
{
	int m;
	linked_list *x;
	char *a;

	for (m = 0; m < 10; m++)
	{
		x = get_node_prefix(func_data->alias, func_data->argv[0], '=');
		if (!x)
			return (0);
		free(func_data->argv[0]);
		a = _strchr(x->ns, '=');
		if (!a)
			return (0);
		a = string_duplicate(a + 1);
		if (!a)
			return (0);
		func_data->argv[0] = a;
	}
	return (1);
}

/**
 * change_ss_vars - changes vars string
 * @func_data: structure containing a data model
 * Return: 1 on Success
 */

int change_ss_vars(sample_type *func_data)
{
	int z;
	linked_list *x;

	for (z = 0; func_data->argv[z]; z++)
	{
		if (func_data->argv[z][0] != '$' || !func_data->argv[z][1])
			continue;
		if (!string_compare(func_data->argv[z], "$?"))
		{
			change_string(&(func_data->argv[z]),
					string_duplicate(number_to_string(func_data->feedback, 10, 0)));
			continue;
		}
		if (!string_compare(func_data->argv[z], "$$"))
		{
			change_string(&(func_data->argv[z]),
					string_duplicate(number_to_string(getpid(), 10, 0)));
			continue;
		}
		x = get_node_prefix(func_data->env, &func_data->argv[z][1], '=');
		if (x)
		{
			change_string(&(func_data->argv[z]),
					string_duplicate(_strchr(x->ns, '=') + 1));
			continue;
		}
		change_string(&(func_data->argv[z]), string_duplicate(""));
	}
	return (0);
}

/**
 * change_string - changes string
 * @ss1: pointer to pointer to first string
 * @ss2: pointer to second string
 * Return: 1 on Success
 */

int change_string(char **ss1, char *ss2)
{
	free(*ss1);
	*ss1 = ss2;
	return (1);
}
