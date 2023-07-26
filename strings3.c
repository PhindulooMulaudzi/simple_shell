#include "shell.h"

/**
 * swap_char - Swaps '|' and '&' for non-printed chars
 *
 * @cmd: cmd string
 * @bool: Type of swap
 * Return: Swapped string
 */
char *swap_char(char *cmd, int bool)
{
	int i;

	if (bool == 0)
	{
		i = 0;
		while (cmd[i])
		{
			if (cmd[i] == '|')
			{
				if (cmd[i + 1] != '|')
					cmd[i] = 16;
				else
					i++;
			}

			if (cmd[i] == '&')
			{
				if (cmd[i + 1] != '&')
					cmd[i] = 12;
				else
					i++;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while (cmd[i])
		{
			cmd[i] = (cmd[i] == 16 ? '|' : cmd[i]);
			cmd[i] = (cmd[i] == 12 ? '&' : cmd[i]);
			i++;
		}
	}
	return (cmd);
}

/**
 * split_line - Tokenizes the cmd string
 *
 * @cmd: cmd string
 * Return: String splitted
 */
char **split_line(char *cmd)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(cmd, TOK_DELIM);
	tokens[0] = token;

	i = 1;
	while (token != NULL)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
		i++;
	}

	return (tokens);
}


/**
 * rev_string - Reverses a string in place.
 * @str: cmd string to be reversed.
 * Return: void.
 */
void rev_string(char *str)
{
	char temp;
	int len = 0;
	char *start = str;
	char *end = str;

	if (str == NULL)
		return;

	while (*end != '\0')
	{
		end++;
		len++;
	}

	end--;

	for (; start < end; start++, end--)
	{
		temp = *start;
		*start = *end;
		*end = temp;
	}
}
