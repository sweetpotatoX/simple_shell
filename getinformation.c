#include "shell.h"

/**
 * clear_info - Initializes an info_t struct by clearing its fields
 * @info: Pointer to the info_t struct to be cleared
 *
 * This function sets all fields of the given info_t struct to NULL or .
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


/**
 * set_info - Initializes an `info_t` struct with the given arguments.
 *
 * @info: A pointer to the `info_t` struct to initialize.
 * @av: The argument vector to use for initialization.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 *
 * This function frees the fields of the info_t struct based on the value of
 * the "all" parameter. If "all" is true, all fields are freed. If "all" is
 * false, only some fields are freed. Specifically, the "argv" and "path"
 * fields are always freed. If "all" is true, the "arg", "env", "history",
 * "alias", "environ", and "cmd_buf" fields are also freed, and the read
 * file descriptor is closed and the output buffer is flushed.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
