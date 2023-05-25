#include "simple_shell.h"

/**
 * exe_command_checker - checks executable command
 * @func_data: structure containing a data model
 * @dir: file direction
 * Return: 1 on Success
 */

int exe_command_checker(sample_type *func_data, char *dir)
{
	struct stat st;

	(void) func_data;
	if (!dir || stat(dir, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * character_duplicate - duplicates characters
 * @dir_s: string needed input
 * @start: start index
 * @stop: stop index
 * Return: pointer to string
 */

char *character_duplicate(char *dir_s, int start, int stop)
{
	static char output[1024];
	int z = 0, x = 0;

	for (x = 0, z = start; z < stop; z++)
		if (dir_s[z] != ':')
			output[x++] = dir_s[z];
	output[x] = 0;
	return (output);
}

/**
 * find_in_dir - find command in a specified direction
 * @func_data: structure containing a data model
 * @dir_s: string needed input
 * @ss: specified command
 * Return: direction string
 */

char *find_in_dir(sample_type *func_data, char *dir_s, char *ss)
{
	int r = 0, a = 0;
	char *dir;

	if (!dir_s)
		return (NULL);
	if ((string_length(ss) > 2) && haystack_start(ss, "./"))
	{
		if (exe_command_checker(func_data, ss))
			return (ss);
	}
	while (1)
	{
		if (!dir_s[r] || dir_s[r] == ':')
		{
			dir = character_duplicate(dir_s, a, r);
			if (!*dir)
				string_cat(dir, ss);
			else
			{
				string_cat(dir, "/");
				string_cat(dir, ss);
			}
			if (exe_command_checker(func_data, dir))
				return (dir);
			if (!dir_s[r])
				break;
			a = r;
		}
		r++;
	}
	return (NULL);
}
