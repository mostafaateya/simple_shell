#include "simple_shell.h"

/**
 * clear_func_data - creates sample-type structure
 * @func_data: structure containing a data model
 * Return: void
 */

void clear_func_data(sample_type *func_data)
{
	func_data->s_cmd = NULL;
	func_data->argv = NULL;
	func_data->path = NULL;
	func_data->argc = 0;
}

/**
 * add_func_data - add sample_type structure
 * @func_data: structure containing a data model
 * @arg: pointer to array of strings
 * Return: void
 */

void add_func_data(sample_type *func_data, char **arg)
{
	int j = 0;

	func_data->file_name = arg[0];
	if (func_data->s_cmd)
	{
		func_data->argv = string_split_2(func_data->s_cmd, " \t");
		if (!func_data->argv)
		{
			func_data->argv = malloc(sizeof(char *) * 2);
			if (func_data->argv)
			{
				func_data->argv[0] = string_duplicate(func_data->s_cmd);
				func_data->argv[1] = NULL;
			}
		}
		for (j = 0; func_data->argv && func_data->argv[j]; j++)
			;
		func_data->argc = j;
		change_ss_alias(func_data);
		change_ss_vars(func_data);
	}
}

/**
 * remove_func_data - removes sample_type structure
 * @func_data: structure containing a data model
 * @success_flag: flag for success remove
 * Return: void
 */

void remove_func_data(sample_type *func_data, int success_flag)
{
	string_free(func_data->argv);
	func_data->argv = NULL;
	func_data->path = NULL;
	if (success_flag)
	{
		if (!func_data->chainning_buffer)
			free(func_data->s_cmd);
		if (func_data->env)
			clear_list(&(func_data->env));
		if (func_data->history)
			clear_list(&(func_data->history));
		if (func_data->alias)
			clear_list(&(func_data->alias));
		string_free(func_data->environ);
		func_data->environ = NULL;
		clear_memory((void **)func_data->chainning_buffer);
		if (func_data->fd_read > 2)
			close(func_data->fd_read);
		_putchar(BUFFER_CLEARING);
	}
}
