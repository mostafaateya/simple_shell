#include "simple_shell.h"

/**
 * add_node_start - adds a new node at the start of linked list
 * @head: pointer to the first node
 * @str: string of node
 * @n: node index
 * Return: length of linked list
 */

linked_list *add_node_start(linked_list **head, const char *str, int n)
{
	linked_list *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(linked_list));
	if (!new_head)
		return (NULL);
	alocate_memory((void *)new_head, 0, sizeof(linked_list));
	new_head->num = n;
	if (str)
	{
		new_head->ns = string_duplicate(str);
		if (!new_head->ns)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->nxt = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a new node at the end of linked list
 * @head: pointer to the first node
 * @str: string of node
 * @n: node index
 * Return: length of linked list
 */

linked_list *add_node_end(linked_list **head, const char *str, int n)
{
	linked_list *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(linked_list));
	if (!new_node)
		return (NULL);
	alocate_memory((void *)new_node, 0, sizeof(linked_list));
	new_node->num = n;
	if (str)
	{
		new_node->ns = string_duplicate(str);
		if (!new_node->ns)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nxt)
			node = node->nxt;
		node->nxt = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_linked_list - prints a string of elements of linked list
 * @n: pointer to the first node
 * Return: length of linked list
 */

size_t print_linked_list(const linked_list *n)
{
	size_t m = 0;

	while (n)
	{
		_puts(n->ns ? n->ns : "(nil)");
		_puts("\n");
		n = n->nxt;
		m++;
	}
	return (m);
}

/**
 * remove_node_index - removes node at a specified index
 * @head: pointer to the first node
 * @index: node index to be removed
 * Return: 1 on Success
 */

int remove_node_index(linked_list **head, unsigned int index)
{
	linked_list *node, *prev_node;
	unsigned int z = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->nxt;
		free(node->ns);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (z == index)
		{
			prev_node->nxt = node->nxt;
			free(node->ns);
			free(node);
			return (1);
		}
		z++;
		prev_node = node;
		node = node->nxt;
	}
	return (0);
}

/**
 * clear_list - clears nodes of linked list
 * @head_p: pointer to the first node
 * Return: void
 */

void clear_list(linked_list **head_p)
{
	linked_list *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->nxt;
		free(node->ns);
		free(node);
		node = next_node;
	}
	*head_p = NULL;
}
