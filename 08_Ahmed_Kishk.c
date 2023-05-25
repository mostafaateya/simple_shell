#include "simple_shell.h"

/**
 * ss_main - main shell loop
 * @func_data: structure containing a data model
 * @arg: the argv vector
 * Return: 0 on Success
 */

int ss_main(sample_type *func_data, char **arg)
{
	ssize_t m = 0;
	int output_value = 0;

	while (m != -1 && output_value != -2)
	{
		clear_func_data(func_data);
		if (play(func_data))
			_puts("$ ");
		error_putchar(BUFFER_CLEARING);
		m = input_get_line(func_data);
		if (m != -1)
		{
			add_func_data(func_data, arg);
			output_value = command_call(func_data);
			if (output_value == -1)
				find_command(func_data);
		}
		else if (play(func_data))
			_putchar('\n');
		remove_func_data(func_data, 0);
	}
	add_history(func_data);
	remove_func_data(func_data, 1);
	if (!play(func_data) && func_data->feedback)
		exit(func_data->feedback);
	if (output_value == -2)
	{
		if (func_data->err_code == -1)
			exit(func_data->feedback);
		exit(func_data->err_code);
	}
	return (output_value);
}

/**
 * command_call - finds commands
 * @func_data: structure containing a data model
 * Return: 0 on Success
 */

int command_call(sample_type *func_data)
{
	int x, output = -1;
	function_table command_table[] = {
		{"exit", ss_exit},
		{"env", ss_env},
		{"help", ss_help},
		{"history", ss_history},
		{"setenv", ss_add_env},
		{"unsetenv", ss_remove_env},
		{"cd", ss_cd},
		{"alias", ss_alias},
		{NULL, NULL}
	};

	for (x = 0; command_table[x]. flag_name; x++)
		if (string_compare(func_data->argv[0], command_table[x].flag_name) == 0)
		{
			func_data->counter_row++;
			output = command_table[x].func_name(func_data);
			break;
		}
	return (output);
}

/**
 * find_command - finds a command
 * @func_data: structure containing a data model
 * Return: void
 */

void find_command(sample_type *func_data)
{
	char *dir = NULL;
	int m, n;

	func_data->path = func_data->argv[0];
	if (func_data->counter_flag == 1)
	{
		func_data->counter_row++;
		func_data->counter_flag = 0;
	}
	for (m = 0, n = 0; func_data->s_cmd[m]; m++)
		if (!_isdeterm(func_data->s_cmd[m], " \t\n"))
			n++;
	if (!n)
		return;
	dir = find_in_dir(func_data, env_value(func_data,
				"PATH="), func_data->argv[0]);
	if (dir)
	{
		func_data->path = dir;
		fork_command(func_data);
	}
	else
	{
		if ((play(func_data) || env_value(func_data,
						"PATH=") || func_data->argv[0][0] == '/')
				&& exe_command_checker(func_data, func_data->argv[0]))
			fork_command(func_data);
		else if (*(func_data->s_cmd) != '\n')
		{
			func_data->feedback = 127;
			error_print(func_data, "not found\n");
		}
	}
}

/**
 * fork_command - forks to run command
 * @func_data: structure containing a data model
 * Return: void
 */

void fork_command(sample_type *func_data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(func_data->path, func_data->argv, get_environ(func_data)) == -1)
		{
			remove_func_data(func_data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(func_data->feedback));
		if (WIFEXITED(func_data->feedback))
		{
			func_data->feedback = WEXITSTATUS(func_data->feedback);
			if (func_data->feedback == 126)
				error_print(func_data, "Permission denied\n");
		}
	}
}
