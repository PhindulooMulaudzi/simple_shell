#include "shell.h"

/**
 * error_path - Generate an error message for failure due to permission denied.
 * @curr_ctxt: Pointer to the ctxt struct containing relevant information.
 * Return: Error message string.
 */
char *error_path(context *curr_ctxt)
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
		error = error_path(curr_ctxt);
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

int check_error_cmd(char *dir, context *curr_ctxt)
{
	int i = 0;
	while (dir[i])
		i++;

	if (dir == NULL)
	{
		get_error(curr_ctxt, 127);
		return (1);
	}

	if (_strcmp(curr_ctxt->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(curr_ctxt, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(curr_ctxt->args[0], X_OK) == -1)
		{
			get_error(curr_ctxt, 126);
			return (1);
		}
	}

	return (0);
}