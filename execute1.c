#include "shell.h"

/**
 * exec_line - finds contexts and commands
 *
 * @curr_ctxt: Relevant context.
 * Return: 1.
 */
int exec_line(context *curr_ctxt)
{
	int (*context)(context *curr_ctxt);

	if (curr_ctxt->args[0] == NULL)
		return (1);

	context = get_context(curr_ctxt->args[0]);

	if (context != NULL)
		return (context(curr_ctxt));

	return (cmd_exec(curr_ctxt));
}

/**
 * exit_shell - exits the shell
 *
 * @curr_ctxt: ctxt relevant (exit_code and args)
 * Return: 0 on success.
 */
int exit_shell(context *curr_ctxt)
{
	unsigned int uexit_code;
	int is_digit;
	int str_len;
	int big_number;

	if (curr_ctxt->args[1] != NULL)
	{
		uexit_code = _atoi(curr_ctxt->args[1]);
		is_digit = _isdigit(curr_ctxt->args[1]);
		str_len = _strlen(curr_ctxt->args[1]);
		big_number = uexit_code > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(curr_ctxt, 2);
			curr_ctxt->exit_code = 2;
			return (1);
		}
		curr_ctxt->exit_code = (uexit_code % 256);
	}
	return (0);
}

/**
 * is_cdir - Check if path in directory
 *
 * @path: path name
 * @i: integer code
 * Return: 1.
 */
int is_cdir(char *path, int *i)
{
	char *p = path;

	if (p[*i] == ':')
		return (1);

	while (p[*i] != ':' && p[*i])
		(*i)++;

	if (p[*i])
		(*i)++;

	return (0);
}

/**
 * _which - Determine command to be executed
 *
 * @cmd: Command
 * @curr_ctxt: Relevant context.
 * Return: 1.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (!path)
		return (NULL);

	ptr_path = _strdup(path);
	if (!ptr_path)
		return (NULL);

	len_cmd = _strlen(cmd);
	token_path = _strtok(ptr_path, ":");
	i = 0;
	while (token_path != NULL)
	{
		if (is_cdir(path, &i))
		{
			if (stat(cmd, &st) == 0)
				return (cmd);
		}
		len_dir = _strlen(token_path);
		dir = malloc(len_dir + len_cmd + 2);
		if (!dir)
		{
			free(ptr_path);
			return (NULL);
		}
		_strcpy(dir, token_path);
		_strcat(dir, "/");
		_strcat(dir, cmd);
		_strcat(dir, "\0");
		if (stat(dir, &st) == 0)
		{
			free(ptr_path);
			return (dir);
		}
		free(dir);
		token_path = _strtok(NULL, ":");
		i = 0;
	}
	free(ptr_path);
	if (stat(cmd, &st) == 0)
		return (cmd);
	return (NULL);
}

/**
 * is_executable - Check if command is valid
 *
 * @curr_ctxt: Relevant context.
 * Return: 1.
 */
int is_executable(context *curr_ctxt)
{
	struct stat st;
	int i = 0;
	char *cmd = curr_ctxt->args[0];

	while (cmd[i])
	{
		if (cmd[i] == '.')
		{
			if (cmd[i + 1] == '.')
				return (0);
			if (cmd[i + 1] == '/')
			{
				i++;
				continue;
			}
			else
				break;
		}
		else if (cmd[i] == '/' && i != 0)
		{
			if (cmd[i + 1] == '.')
			{
				i++;
				continue;
			}
			i++;
			break;
		}
		else
			break;
		i++;
	}

	if (i == 0)
		return (0);

	if (stat(cmd + i, &st) == 0)
	{
		return (i);
	}
	get_error(curr_ctxt, 127);
	return (-1);
}