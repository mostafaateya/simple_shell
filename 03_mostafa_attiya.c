#include "simple_shell.h"

/**
 * ss_cd - changes the current directory
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_cd(sample_type *func_data)
{
	char *m, *dir;
	char buf[1024];
	int chdir_return;

	m = getcwd(buf, 1024);
	if (!m)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!func_data->argv[1])
	{
		dir = env_value(func_data, "HOME=");
		if (!dir)
			chdir_return = chdir((dir = env_value(func_data, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (string_compare(func_data->argv[1], "-") == 0)
	{
		if (!env_value(func_data, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(env_value(func_data, "OLDPWD=")), _putchar('\n');
		chdir_return = chdir((dir = env_value(func_data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(func_data->argv[1]);
	if (chdir_return == -1)
	{
		error_print(func_data, "can't cd to ");
		error_string_print(func_data->argv[1]);
		error_putchar('\n');
	}
	else
	{
		add_env(func_data, "OLDPWD", env_value(func_data, "PWD="));
		add_env(func_data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * ss_exit - exits simple shell
 * @func_data: structure containing a data model
 * Return: 0 on Success
 */

int ss_exit(sample_type *func_data)
{
	int checker;

	if (func_data->argv[1])
	{
		checker = error_atoi(func_data->argv[1]);
		if (checker == -1)
		{
			func_data->feedback = 2;
			error_print(func_data, "Illegal number: ");
			error_string_print(func_data->argv[1]);
			error_putchar('\n');
			return (1);
		}
		func_data->err_code = error_atoi(func_data->argv[1]);
		return (-2);
	}
	func_data->err_code = -1;
	return (-2);
}

/**
 * ss_help - executes a help command
 * @func_data: structure containing a data model
 * Return: 0 Always
 */

int ss_help(sample_type *func_data)
{
	char **rg;

	rg = func_data->argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*rg);
	return (0);
}
