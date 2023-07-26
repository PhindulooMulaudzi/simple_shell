#include "shell.h"

/**
 * exec_line - finds contexts and commands
 *
 * @curr_ctxt: ctxt relevant (args)
 * Return: 1 on success.
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

int cmd_exec(context *curr_ctxt)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void)wpd;

	exec = is_executable(curr_ctxt);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(curr_ctxt->args[0], curr_ctxt->_environ);
		if (check_error_cmd(dir, curr_ctxt) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(curr_ctxt->args[0], curr_ctxt->_environ);
		else
			dir = curr_ctxt->args[0];
		execve(dir + exec, curr_ctxt->args, curr_ctxt->_environ);
	}
	else if (pd < 0)
	{
		perror(curr_ctxt->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	curr_ctxt->exit_code = state / 256;
	return (1);
}
