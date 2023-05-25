#include "simple_shell.h"

/**
 * linked_list_length - determines length of linked list
 * @n: pointer to first node
 * Return: length of linked list
 */

size_t linked_list_length(const linked_list *n)
{
	size_t z;

	for (z = 0; n; z++)
		n = n->nxt;
	return (z);
}

/**
 * linked_list_array - returns an array of strings of list->ns
 * @head: pointer to the first node
 * Return: array of strings
 */

char **linked_list_array(linked_list *head)
{
	linked_list *node = head;
	size_t m = linked_list_length(head);
	size_t n;
	char **sss;
	char *ss;

	if (!head || !m)
		return (NULL);
	sss = malloc(sizeof(char *) * (m + 1));
	if (!sss)
		return (NULL);
	for (m = 0; node; node = node->nxt, m++)
	{
		ss = malloc(string_length(node->ns) + 1);
		if (!ss)
		{
			for (n = 0; n < m; n++)
				free(sss[n]);
			free(sss);
			return (NULL);
		}
		ss = string_copy(ss, node->ns);
		sss[m] = ss;
	}
	sss[m] = NULL;
	return (sss);
}

/**
 * print_list - prints all elements of a linked list
 * @n: pointer to the first node
 * Return: length of linked list
 */

size_t print_list(const linked_list *n)
{
	size_t r;

	for (r = 0; n; r++)
	{
		_puts(number_to_string(n->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(n->ns ? n->ns : "(nil)");
		_puts("\n");
		n = n->nxt;
	}
	return (r);
}

/**
 * get_node_prefix - returns node which has a specified prefix
 * @node: pointer to first node
 * @prefix: string input needed
 * @c: character input
 * Return: matched node
 */

linked_list *get_node_prefix(linked_list *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = haystack_start(node->ns, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->nxt;
	}
	return (NULL);
}

/**
 * node_index - gets index of a node
 * @head: pointer to the first node
 * @node: pointer to a node
 * Return: index of a node
 */

ssize_t node_index(linked_list *head, linked_list *node)
{
	size_t z;

	for (z = 0; head; z++)
	{
		if (head == node)
			return (z);
		head = head->nxt;
	}
	return (-1);
}
