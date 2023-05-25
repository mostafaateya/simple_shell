#include "simple_shell.h"

/**
 * get_environ - returns a string from an environment
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

char **get_environ(sample_type *func_data)
{
	if (!func_data->environ || func_data->changedflag)
	{
		func_data->environ = linked_list_array(func_data->env);
		func_data->changedflag = 0;
	}
	return (func_data->environ);
}

/**
 * remove_env - removes an environment
 * @func_data: structure containing a data model
 * @ss: string of environment property
 * Return: 1 on Success
 */

int remove_env(sample_type *func_data, char *ss)
{
	linked_list *x = func_data->env;
	size_t r = 0;
	char *c;

	if (!x || !ss)
		return (0);
	while (x)
	{
		c = haystack_start(x->ns, ss);
		if (c && *c == '=')
		{
			func_data->changedflag = remove_node_index(&(func_data->env), r);
			r = 0;
			x = func_data->env;
			continue;
		}
		x = x->nxt;
		r++;
	}
	return (func_data->changedflag);
}

/**
 * add_env - create a new environment
 * @func_data: structure containing a data model
 * @ss: string of an environment property
 * @ss_value: string of environment variable value
 * Return: 0 Always
 */

int add_env(sample_type *func_data, char *ss, char *ss_value)
{
	char *a = NULL;
	linked_list *x;
	char *c;

	if (!ss || !ss_value)
		return (0);
	a = malloc(string_length(ss) + string_length(ss_value) + 2);
	if (!a)
		return (1);
	string_copy(a, ss);
	string_cat(a, "=");
	string_cat(a, ss_value);
	x = func_data->env;
	while (x)
	{
		c = haystack_start(x->ns, ss);
		if (c && *c == '=')
		{
			free(x->ns);
			x->ns = a;
			func_data->changedflag = 1;
			return (0);
		}
		x = x->nxt;
	}
	add_node_end(&(func_data->env), a, 0);
	free(a);
	func_data->changedflag = 1;
	return (0);
}
