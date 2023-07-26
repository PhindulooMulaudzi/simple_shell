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

	ver_str = itostr(curr_ctxt->count);
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

	ver_str = itostr(curr_ctxt->count);
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

	ver_str = itostr(curr_ctxt->count);
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

	ver_str = itostr(curr_ctxt->count);
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
