#include "shell.h"

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: Destination string.
 * @src: Source string.
 * Return:Concatenated string.
 */
char *_strcat(char *dest, const char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return dest;
}

/**
 * _strcpy - Copies a string.
 *
 * @dest: Destination.
 * @src: Source.
 * Return: Copy of source
 */
char *_strcpy(char *dest, char *src)
{
	size_t a = 0;

	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}

	dest[a] = '\0';
	return dest;
}

/**
 * _strcmp - Compare two strings.
 *
 * @s1: First string.
 * @s2: Second string.
 * Return: 1 or 0
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;

	if (s1[i] > s2[i])
		return 1;
	if (s1[i] < s2[i])
		return -1;
	return 0;
}

/**
 * _strchr - Find character in string.
 *
 * @s: String.
 * @c: Character to find.
 * Return: Ptr to first char occurence
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	while (*(s + i) != '\0')
	{
		if (*(s + i) == c)
			return (s + i);
		i++;
	}
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}

/**
 * _strspn - Get length of a substring.
 *
 * @s: String segment
 * @accept: Accepted bytes
 * Return: Number of bytes
 */
int _strspn(char *s, char *accept)
{
	int i = 0, j = 0, bool;

	while (s[i] != '\0')
	{
		bool = 1;
		j = 0;

		while (accept[j] != '\0')
		{
			if (s[i] == accept[j])
			{
				bool = 0;
				break;
			}
			j++;
		}

		if (bool == 1)
			break;

		i++;
	}

	return (i);
}
