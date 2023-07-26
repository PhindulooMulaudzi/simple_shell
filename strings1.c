#include "shell.h"

/**
 * _strcat - Concatenate two strings.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 * Return: Pointer to the destination buffer.
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
 * _strcpy - Copy the string pointed to by src.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 * Return: Pointer to the destination buffer.
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
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 * Return: 0 if strings are equal, 1 if s1 is greater, -1 if s2 is greater.
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
 * _strchr - Locate a character in a string.
 * @s: Pointer to the string.
 * @c: Character to locate.
 * Return: Pointer to the first occurrence of the character c, or NULL if not found.
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
 * _strspn - Get the length of a prefix substring.
 * @s: Pointer to the initial segment.
 * @accept: Pointer to the accepted bytes.
 * Return: The number of accepted bytes.
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
