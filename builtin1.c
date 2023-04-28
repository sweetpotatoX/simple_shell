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
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *point; /* pointer to the location of the '=' character */
	int retu; /* return value */

	point = _strchr(str, '='); /* find location of the '=' character in the string */
	if (!point) /* if no '=' character found */
		return (1); /* return 1 to indicate error */
	char ch = *point; /* save the character at the location of the '=' character */
	*point = '\0'; /* set the character at the location of the '=' to null terminator */
	retu = delete_node_at_index(&(info->alias), /* delete the alias node */
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*point = ch; /* restore the character at the location of the '=' character */
	return (retu); /* return the return value of delete_node_at_index() */
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *point;

	/* Find the first '=' in the string */
	point = _strchr(str, '=');
	if (!point)
		return (1);

	/* Check if the alias value is empty */
	if (!*++point)
		return (unset_alias(info, str));

	/* Remove any existing alias with the same name */
	unset_alias(info, str);

	/* Add the new alias to the end of the alias linked list */
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
	char *p = NULL, *af = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (af = node->str; af <= p; af++)
			_putchar(*af);
		_putchar('\'');
		_puts(p + 1); /*Print everything after the '=' character*/
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int index = 0;
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
	for (index = 1; info->argv[index]; index++)
	{
		p = _strchr(info->argv[index], '=');
		if (p)
			set_alias(info, info->argv[index]);
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}
