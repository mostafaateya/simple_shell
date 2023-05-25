#include "simple_shell.h"

/**
 * ss_env - prints the current environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_env(sample_type *func_data)
{
	print_linked_list(func_data->env);
	return (0);
}

/**
 * ss_add_env - creates a new environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_add_env(sample_type *func_data)
{
	if (func_data->argc != 3)
	{
		error_string_print("Incorrect number of arguments\n");
		return (1);
	}
	if (add_env(func_data, func_data->argv[1], func_data->argv[2]))
		return (0);
	return (1);
}

/**
 * ss_remove_env - removes an existing environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_remove_env(sample_type *func_data)
{
	int n;

	if (func_data->argc == 1)
	{
		error_string_print("Too few arguments.\n");
		return (1);
	}
	for (n = 1; n <= func_data->argc; n++)
		remove_env(func_data, func_data->argv[n]);
	return (0);
}

/**
 * linked_list_env - creates environment linked list
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int linked_list_env(sample_type *func_data)
{
	linked_list *x = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_node_end(&x, environ[m], 0);
	func_data->env = x;
	return (0);
}

/**
 * env_value - gets a value of an environment
 * @func_data: structure containing a data model
 * @env_name: environment name
 * Return: value of an environment
 */

char *env_value(sample_type *func_data, const char *env_name)
{
	linked_list *x = func_data->env;
	char *r;

	while (x)
	{
		r = haystack_start(x->ns, env_name);
		if (r && *r)
			return (r);
		x = x->nxt;
	}
	return (NULL);
}
