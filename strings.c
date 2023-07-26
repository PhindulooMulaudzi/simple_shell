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


/**
 * _strdup - Duplicate a string in the heap memory.
 * @s: Pointer to the cmd string.
 * Return: Duplicated string on success, NULL on failure.
 */
char *_strdup(const char *s)
{
	char *new_str;
	size_t len;

	len = _strlen(s);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	_memcpy(new_str, s, len + 1);
	return (new_str);
}

/**
 * _strlen - Returns the length of a string.
 * @s: Pointer to the cmd string.
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != '\0'; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - Compare characters of strings.
 * @str: cmd string.
 * @delim: Delimiter string.
 *
 * Return: 1 if characters are equal, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - Splits a string by a given delimiter.
 * @str: cmd string.
 * @delim: Delimiter string.
 *
 * Return: A pointer to the next token, NULL if no more tokens.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /* Store the first address */
		i = _strlen(str);
		str_end = &str[i]; /* Store the last address */
	}
	str_start = splitted;
	if (str_start == str_end) /* Reaching the end */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* Breaking the loop finding the next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/* Replacing delimiter for a null char */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /* Str != Delim */
			bool = 1;
	}
	if (bool == 0) /* Str == Delim */
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - Defines if a string contains only digits (0-9).
 *
 * @s: cmd string.
 * Return: 1 if the string contains only digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

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
 * add_nodes - Adds separators and command lines to the lists
 *
 * @head_s: Head of the separator list
 * @head_l: Head of the command lines list
 * @cmd: cmd string
 * Return: No return
 */
void add_nodes(separator **head_s, cmd_line **head_l, char *cmd)
{
	int i;
	char *line;

	cmd = swap_char(cmd, 0);

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';')
			add_separator(head_s, cmd[i]);

		if (cmd[i] == '|' || cmd[i] == '&')
		{
			add_separator(head_s, cmd[i]);
			i++;
		}
		i++;
	}

	line = _strtok(cmd, ";|&");
	do {
		line = swap_char(line, 1);
		add_cmd(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * go_next - Goes to the next command line stored
 *
 * @list_s: Separator list
 * @list_l: Command line list
 * @curr_ctxt: ctxt structure
 * Return: No return
 */
void go_next(separator **list_s, cmd_line **list_l, context *curr_ctxt)
{
	int loop_sep;
	separator *ls_s;
	cmd_line *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (curr_ctxt->exit_code == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - Splits command lines according to the separators: ;, |, and & and executes them
 *
 * @curr_ctxt: ctxt structure
 * @cmd: cmd string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(context *curr_ctxt, char *cmd)
{
	separator *head_s, *list_s;
	cmd_line *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, cmd);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		curr_ctxt->cmd = list_l->line;
		curr_ctxt->args = split_line(curr_ctxt->cmd);
		loop = exec_line(curr_ctxt);
		free(curr_ctxt->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, curr_ctxt);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_separator(&head_s);
	free_cmd(&head_l);

	if (loop == 0)
		return (0);
	return (1);
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
