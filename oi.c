#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int l, brand = 1, drag = 0, output;
	unsigned int result = 0;

	for (l = 0; s[l] != '\0' && drag != 2; l++)
	{
		if (s[l] == '-')
			brand *= -1;
		if (s[l] >= '0' && s[l] <= '9')
		{
			drag = 1;
			result *= 10;
			result += (s[l] - '0');
		}
		else if (drag == 1)
			drag = 2;
	}

	if (brand == -1)
		output = -result;
	else
		output = result;

	return (output);
}
