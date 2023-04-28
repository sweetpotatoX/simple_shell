#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from the alias list
 * @info: pointer to a structure containing program information
 * @str: string containing the alias to be removed
 *
 * Return: 0 on success, 1 on failure
 */
int unset_alias(info_t *info, char *str)
{
	char *p, ch;
	int ret;

	/* Find the position of the '=' character in the string */
	p = _strchr(str, '=');
	if (!p)
		return (1);

	/* Save the character that follows the '=' character */
	ch = *p;
	*p = 0;

	/* Remove the alias from the alias list */
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	/* Restore the character that followed the '=' character */
	*p = ch;

	return (ret);
}


/**
 * set_alias - sets an alias to a given string
 * @info: parameter struct
 * @str: the string containing the alias and its value
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	/* Find the location of the '=' character in the input string */
	p = _strchr(str, '=');
	if (!p)
		return (1); /* Return an error if there is no '=' character */

	/* If the character immediately following the '=' is a null terminator, unset the alias */
	if (!*++p)
		return (unset_alias(info, str));

	/* Unset any existing alias with the same name before setting the new one */
	unset_alias(info, str);

	/* Add the new alias to the end of the list of aliases */
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *pread = NULL, *accesss = NULL;

	if (node)
	{
		pread = _strchr(node->str, '=');
		for (accesss = node->str; accesss <= pread; accesss++)
			_putchar(*accesss);
		_putchar('\'');
		_puts(pread + 1);
		_puts("'\n");
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
	int index = 0;
	char *pread = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node); // print each alias node
			node = node->next;
		}
		return (0);
	}

	for (index = 1; info->argv[index]; index++)
	{
		pread = _strchr(info->argv[index], '=');
		if (pread)
			set_alias(info, info->argv[index]); // set alias
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '=')); // print alias node that matches pattern
	}

	return (0);
}
