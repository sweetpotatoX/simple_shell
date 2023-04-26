#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	list_t *current = info->history;
	unsigned int count = 0;

	while (current)
	{
		printf("%u ", count++);
		puts(current->str);
		current = current->next;
	}

	return (0);
}

/**
 * unset_alias - removes an alias from the alias linked list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 if the alias was successfully removed, 1 otherwise
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strchr(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = '\0';

	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*p = c;
	return (ret);
}

/**
 * set_alias - adds an alias to the alias linked list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 if the alias was successfully added, 1 otherwise
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = strchr(str, '=');
	if (!p)
		return (1);

	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 if the alias was successfully printed, 1 otherwise
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			putchar(*a);

		putchar('\'');
		puts(p + 1);

		return (0);
	}

	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = strchr(info->argv[i], '=');

		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

