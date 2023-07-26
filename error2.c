#include "shell.h"

/**
 * count_repeated_char - counts the repetitions of a char
 *
 * @cmd: command string
 * @i: index
 * Return: repetitions
 */
int count_repeated_char(char *cmd, int i)
{
	if (*(cmd - 1) == *cmd)
		return (count_repeated_char(cmd - 1, i + 1));

	return (i);
}

/**
 * find_syntax_error - finds syntax errors
 *
 * @cmd: command string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no errors
 */
int find_syntax_error(char *cmd, int i, char last)
{
	int count;

	count = 0;
	if (*cmd == '\0')
		return (0);

	if (*cmd == ' ' || *cmd == '\t')
		return (find_syntax_error(cmd + 1, i + 1, last));

	if (*cmd == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*cmd == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = count_repeated_char(cmd, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*cmd == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = count_repeated_char(cmd, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (find_syntax_error(cmd + 1, i + 1, *cmd));
}

/**
 * find_first_char - finds index of the first char
 *
 * @cmd: command string
 * @i: index
 * Return: 1 if there is an error. 0 in other cases.
 */
int find_first_char(char *cmd, int *i)
{
	for (*i = 0; cmd[*i]; *i += 1)
	{
		if (cmd[*i] == ' ' || cmd[*i] == '\t')
			continue;

		if (cmd[*i] == ';' || cmd[*i] == '|' || cmd[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @curr_ctxt: current context
 * @cmd: command string
 * @i: index of the error
 * @bool: to control message error
 * Return: void
 */
void print_syntax_error(context *curr_ctxt, char *cmd, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *count;
	int length;

	if (cmd[i] == ';')
	{
		if (bool == 0)
			msg = (cmd[i + 1] == ';' ? ";;" : ";");
		else
			msg = (cmd[i - 1] == ';' ? ";;" : ";");
	}

	if (cmd[i] == '|')
		msg = (cmd[i + 1] == '|' ? "||" : "|");

	if (cmd[i] == '&')
		msg = (cmd[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	count = itostr(curr_ctxt->count);
	length = _strlen(curr_ctxt->argv[0]) + _strlen(count);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	_strcpy(error, curr_ctxt->argv[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(count);
}

/**
 * check_syntax_error - intermediate function to find and print a syntax error
 *
 * @curr_ctxt: current context
 * @cmd: command string
 * Return: 1 if there is an error. 0 in other cases
 */
int check_syntax_error(context *curr_ctxt, char *cmd)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = find_first_char(cmd, &begin);
	if (f_char == -1)
	{
		print_syntax_error(curr_ctxt, cmd, begin, 0);
		return (1);
	}

	i = find_syntax_error(cmd + begin, 0, *(cmd + begin));
	if (i != 0)
	{
		print_syntax_error(curr_ctxt, cmd, begin + i, 1);
		return (1);
	}

	return (0);
}
