#include "simple_shell.h"

/**
 * clear_memory - frees alocated memory
 * @p: pointer to free
 * Return: 1 on Success
 */

int  clear_memory(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
