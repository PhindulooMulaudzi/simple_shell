#include "shell.h"

/**
 * cderr_concat - function that concatenates the message for cd error
 *
 * @curr_ctxt: ctxt relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: count lines
 * Return: error message
 */
char *cderr_concat(context *curr_ctxt, char *msg, char *error, char *ver_str)
{
	char *flag;

	_strcpy(error, curr_ctxt->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, curr_ctxt->args[0]);
	_strcat(error, msg);
	if (curr_ctxt->args[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = curr_ctxt->args[1][1];
		flag[2] = '\0';
		_strcat(error, flag);
		free(flag);
	}
	else
	{
		_strcat(error, curr_ctxt->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @curr_ctxt: ctxt relevant (directory)
 * Return: Error message
 */
char *error_get_cd(context *curr_ctxt)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(curr_ctxt->count);
	if (curr_ctxt->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(curr_ctxt->args[1]);
	}

	length = _strlen(curr_ctxt->argv[0]) + _strlen(curr_ctxt->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = cderr_concat(curr_ctxt, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @curr_ctxt: ctxt relevant (count, arguments)
 * Return: Error message
 */
char *error_not_found(context *curr_ctxt)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(curr_ctxt->count);
	length = _strlen(curr_ctxt->argv[0]) + _strlen(ver_str);
	length += _strlen(curr_ctxt->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, curr_ctxt->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, curr_ctxt->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @curr_ctxt: ctxt relevant (count, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(context *curr_ctxt)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(curr_ctxt->count);
	length = _strlen(curr_ctxt->argv[0]) + _strlen(ver_str);
	length += _strlen(curr_ctxt->args[0]) + _strlen(curr_ctxt->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, curr_ctxt->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, curr_ctxt->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, curr_ctxt->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}

/**
 * error_env - Generate an error message for the environment-related functions.
 * @curr_ctxt: Pointer to the ctxt struct containing relevant information.
 * Return: Error message string.
 */
char *error_env(context *curr_ctxt)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(curr_ctxt->count);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(curr_ctxt->argv[0]) + _strlen(ver_str);
	length += _strlen(curr_ctxt->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, curr_ctxt->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, curr_ctxt->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * error_path_126 - Generate an error message for failure due to permission denied.
 * @curr_ctxt: Pointer to the ctxt struct containing relevant information.
 * Return: Error message string.
 */
char *error_path_126(context *curr_ctxt)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(curr_ctxt->count);
	length = _strlen(curr_ctxt->argv[0]) + _strlen(ver_str);
	length += _strlen(curr_ctxt->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, curr_ctxt->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, curr_ctxt->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * get_error - calls the error according the context, syntax or permission
 * @curr_ctxt: ctxt structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(context *curr_ctxt, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(curr_ctxt);
		break;
	case 126:
		error = error_path_126(curr_ctxt);
		break;
	case 127:
		error = error_not_found(curr_ctxt);
		break;
	case 2:
		if (_strcmp("exit", curr_ctxt->args[0]) == 0)
			error = error_exit_shell(curr_ctxt);
		else if (_strcmp("cd", curr_ctxt->args[0]) == 0)
			error = error_get_cd(curr_ctxt);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	curr_ctxt->exit_code = eval;
	return (eval);
}


/**
 * count_repeated_char - counts the repetitions of a char
 *
 * @cmd: cmd string
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
 * @cmd: cmd string
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
 * @cmd: cmd string
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
 * @curr_ctxt: ctxt structure
 * @cmd: cmd string
 * @i: index of the error
 * @bool: to control message error
 * Return: no return
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
	count = aux_itoa(curr_ctxt->count);
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
 * @curr_ctxt: ctxt structure
 * @cmd: cmd string
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
