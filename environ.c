#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env variable name
 *
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *k;

	while (node)
	{
		/* Get a pointer to the value of the environment variable if it matches the given name */
		k = starts_with(node->str, name);
		if (k && *k) /* Ensure that a non-empty string was returned */
			return (k);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *
 * Return: 0 on success, 1 on error
 */
int _mysetenv(info_t *info)
{
	/* Check if correct number of arguments is passed */
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	/* Set environment variable */
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}


/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	
	/* Loop through all arguments and remove corresponding environment variables */
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);
}


/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&node, environ[index], 0);
	info->env = node;
	return (0);
}
