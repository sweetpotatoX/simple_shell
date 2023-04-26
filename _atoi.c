#include "shell.h"

/**
 * interactive - returns 1 if shell is in input mode
 * @info: adress of shell
 *
 * Return: 1 if input mode, 0 if not
 */
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if char is a separator.
 * @c: the char we want to check
 * @delim: the separator string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, const char *delim)
{
	int i;
    for ( i = 0; delim[i] != '\0'; i++)
    {
        if (c == delim[i]) {
            return 1;
        }
    }
    return 0;
}


/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int string_to_int(char *s)
{
    int result = 0;
    int sign = 1;
    int i;

    if (s[0] == '-')
    {
        sign = -1;
        s++;
    }

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result = result * 10 + (s[i] - '0');
        }
        else
        {
            break;
        }
    }

    return result * sign;
}

