#include "shell.h"
/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: number of bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}


/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t index1, index2, lenth;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &buffer, &lenth);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (lenth) /* we have commands left in the chain buffer */
	{
		index2 = index1; /* init new iterator to current buf position */
		p = buffer + index1; /* get pointer for return */

		check_chain(info, buffer, &index2, index1, lenth);
		while (index2 < lenth) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &index2))
				break;
			index2++;
		}

		index1 = index2 + 1; /* increment past nulled ';'' */
		if (index1 >= lenth) /* reached end of buffer? */
		{
			index1 = lenth = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (bytes_read); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer to read into
 * @i: pointer to size of buffer
 *
 * Return: number of bytes read
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: number of bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t index, lenth;
	size_t ker;
	ssize_t rek = 0, str = 0;
	char *point = NULL, *new_point = NULL, *c;

	point = *ptr;
	if (point && length)
		str = *length;
	if (index == lenth)
		index = lenth = 0;

	rek = read_buf(info, buffer, &lenth);
	if (rek == -1 || (rek == 0 && lenth == 0))
		return (-1);

	c = _strchr(buffer + index, '\n');
	ker = c ? 1 + (unsigned int)(c - buffer) : lenth;
	new_point = _realloc(point, str, str ? str + ker : ker + 1);
	if (!new_point) /* MALLOC FAILURE! */
		return (point ? free(point), -1 : -1);

	if (str)
		_strncat(new_point, buffer + index, ker - index);
	else
		_strncpy(new_point, buffer + index, ker - index + 1);

	str += ker - index;
	index = ker;
	point = new_point;

	if (length)
		*length = str;
	*ptr = point;
	return (str);
}
/**
 * sigintHandler - function that handles the SIGINT signal (ctrl-C)
 * @sig_num: the signal number (unused)
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n"); /* print a new line */
	_puts("$ "); /* print the shell prompt */
	_putchar(BUF_FLUSH); /* flush the output buffer */
}
