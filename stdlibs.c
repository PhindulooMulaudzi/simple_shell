#include "shell.h"

/**
 * num_length - Length of an integer.
 * @n: integer.
 * Return: Length.
 */
int num_length(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = (unsigned int)(-n);
	}
	else
	{
		n1 = (unsigned int)n;
	}

	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}

/**
 * itostr - Change integer to a string.
 * @n: Integer number.
 * Return: String
 */
char *itostr(int n)
{
	unsigned int n1;
	int length = num_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == NULL)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		n1 = (unsigned int)(-n);
		buffer[0] = '-';
	}
	else
	{
		n1 = (unsigned int)n;
	}

	length--;
	do {
		*(buffer + length) = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	} while (n1 > 0);

	return (buffer);
}

/**
 * _atoi - Change a string to integer.
 * @s: String.
 * Return: Integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - '0') * m);
		m /= 10;
	}

	return (oi * pn);
}
