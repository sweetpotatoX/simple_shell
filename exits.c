#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int index1, index2;
	char *str = dest;

	index1 = 0;
	while (src[index1] != '\0' && index1 < n - 1)
	{
		dest[index1] = src[index1];
		index1++;
	}
	if (index1 < n)
	{
		index2 = index1;
		while (index2 < n)
		{
			dest[index2] = '\0';
			index2++;
		}
	}
	return (str);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string to concatenate
 * @src: the second string to concatenate
 * @n: the maximum number of bytes to be used from src
 *
 * Return: pointer to the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int index1, index2;
	char *str = dest;

	/* Find the end of the first string */
	index1 = 0;
	while (dest[index1] != '\0')
		index1++;

	/* Append the second string to the first string */
	index2 = 0;
	while (src[index2] != '\0' && index2 < n)
	{
		dest[index1] = src[index2];
		index1++;
		index2++;
	}

	/* Add null terminator to the end of the concatenated string */
	if (index2 < n)
		dest[index1] = '\0';

	return (str);
}

/**
 * _strchr - locates the first occurrence of a character in a string.
 * @s: the string to be searched
 * @c: the character to be located
 *
 * Return: pointer to the first occurrence of the character c in the string s,
 * or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
