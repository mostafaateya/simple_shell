#include "simple_shell.h"

/**
 * alocate_memory - fills memory with byte
 * @p: pointer to memory
 * @c: filled byte
 * @n: number of bytes
 * Return: pointer to memory
 */

char *alocate_memory(char *p, char c, unsigned int n)
{
	unsigned int z;

	for (z = 0; z < n; z++)
		p[z] = c;
	return (p);
}

/**
 * string_free - frees a string from memory
 * @ss: specified string
 * Return: void
 */

void string_free(char **ss)
{
	char **c = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(c);
}

/**
 * _realloc - reallocated a block of memory
 * @ptr: pointer to the previous block
 * @old_block: size of previous block
 * @new_block: size of new block
 * Return: void
 */

void *_realloc(void *ptr, unsigned int old_block, unsigned int new_block)
{
	char *c;

	if (!ptr)
		return (malloc(new_ block));
	if (!new_ block)
		return (free(ptr), NULL);
	if (new_ block == old_block)
		return (ptr);
	c = malloc(new_ block);
	if (!c)
		return (NULL);
	old_block = old_block < new_ block ? old_block : new_ block;
	while (old_block--)
		p[old_block] = ((char *)ptr)[old_block];
	free(ptr);
	return (c);
}
