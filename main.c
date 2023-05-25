#include "simple_shell.h"

/**
 * main - main program
 * @margc: argc counter
 * @margv: argv vector
 * Return: 0 on Success
 */

int main(int margc, char **margv)
{
	sample_type func_data[] = {{NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
		{0}, {0}, {0}, {0}, {0}, {0}, {NULL}, {NULL}, {NULL}, {0}, {0}, {0}};
	int x = 2;

	asm ("mov %1, %0\n\tadd $3, %0" : "=r" (x) : "r" (x));

	if (margc == 2)
	{
		x = open(margv[1], O_RDONLY);
		if (x == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_string_print(margv[0]);
				error_string_print(": 0: Can't open ");
				error_string_print(margv[1]);
				error_putchar('\n');
				error_putchar(BUFFER_CLEARING);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		func_data->fd_read = x;
	}
	linked_list_env(func_data);
	history_row(func_data);
	ss_main(func_data, margv);
	return (EXIT_SUCCESS);
}
