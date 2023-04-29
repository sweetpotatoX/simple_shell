#include "shell.h"

/**
 * get_history_file - Gets the path to the history file.
 * @info: Parameter struct containing environment variables.
 *
 * Return: Pointer to allocated string containing the path to the history file.
 * NULL if directory cannot be found or memory allocation fails.
 */
char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	/* Get the path to home directory from the environment variables. */
	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);

	/* Allocate memory for the buffer to hold the path to the history file. */
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);

	/* Return the buffer with the path to the history file. */
	return (buffer);
}

/**
 * write_history - Writes the command history to a file
 * @info: The parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: the number of items read from the history file, 0 otherwise
 */
int read_history(info_t *info)
{
	int index, l = 0, lc = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filn = get_history_file(info);
	
	if (!filn)
		return (0);

	fd = open(filn, O_RDONLY);
	free(filn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (index = 0; index < fsize; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			build_history_list(info, buffer + l, lc++);
			l = index + 1;
		}
	if (l != index)
		build_history_list(info, buffer + l, lc++);
	free(buffer);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}


/**
 * build_history_list - Adds entry to a history linked list
 * @info: A structure containing potential arguments. Used to maintain
 *        the history line count.
 * @buf: The buffer containing the command string to be added to the history.
 * @linecount: The current history line count.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int index = 0;

	while (node)
	{
		node->num = index++;
		node = node->next;
	}

	return (info->histcount = index);
}
