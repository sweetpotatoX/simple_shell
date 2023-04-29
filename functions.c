#include <string.h>
#include "shell.h"
/**
 * _strlen - checks for the length of a string
 * @s: string parameter
 *
 * Return: 0 success
 */
int _strlen(char *s)
{
	int len;

	len = strlen(s);
	return (len);
}

/**
 * _strcat - concatenates strings
 * @dest: destination string
 * @src: source string
 *
 * Return: dest on success
 */
char *_strcat(char *dest, char *src)
{
	strcat(dest, src);
	return (dest);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
