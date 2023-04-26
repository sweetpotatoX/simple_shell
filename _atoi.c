#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
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

int is_alpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}
/**
 * _atoi - converts a string to an integer.
 * @s: An input string.
 * Return: 0 if no numbers in string, converted number if not.
 */
int _atoi(char *s)
{
    int sign = 1;
    unsigned int total = 0;
    char null_flag = 0;

    if (s == NULL)
        return (0);
    while (*s)
    {
        if (*s == '-')
            sign *= -1;
        if (*s >= '0' && *s <= '9')
        {
            null_flag = 1;
            total = total * 10 + (*s - '0');
        }
        else if (*s == '+' && null_flag == 0)
        {
            null_flag = 1;
        }
        else if (*s < '0' || *s > '9')
        {
            if (null_flag == 1)
                break;
        }
        s++;
    }
if (sign < 0)
total = (-1 * (total));
return (total);
}
