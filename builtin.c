#include "shell.h"

/**
 * get_context - context for the command
 * @cmd: command
 * Return: context ptr
 */
int (*get_context(char *cmd))(context *)
{
	builtin context[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; context[i].name; i++)
	{
		if (_strcmp(context[i].name, cmd) == 0)
			break;
	}

	return (context[i].f);
}

/**
 * set_env - sets environment variable
 *
 * @name: variable name
 * @value: variable value
 * @curr_ctxt: context
 * Return: void
 */
void set_env(char *name, char *value, context *curr_ctxt)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; curr_ctxt->_environ[i]; i++)
	{
		var_env = _strdup(curr_ctxt->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(curr_ctxt->_environ[i]);
			curr_ctxt->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	curr_ctxt->_environ =
	_reallocdptr(curr_ctxt->_environ, i, sizeof(char *) * (i + 2));
	curr_ctxt->_environ[i] = copy_info(name, value);
	curr_ctxt->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares environment variables
 * @curr_ctxt: current context.
 *
 * Return: 1.
 */
int _setenv(context *curr_ctxt)
{

	if (curr_ctxt->args[1] == NULL || curr_ctxt->args[2] == NULL)
	{
		get_error(curr_ctxt, -1);
		return (1);
	}

	set_env(curr_ctxt->args[1], curr_ctxt->args[2], curr_ctxt);

	return (1);
}

/**
 * _unsetenv - deletes environment variable
 *
 * @curr_ctxt: current context.
 *
 * Return: 1.
 */
int _unsetenv(context *curr_ctxt)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (curr_ctxt->args[1] == NULL)
	{
		get_error(curr_ctxt, -1);
		return (1);
	}
	k = -1;
	for (i = 0; curr_ctxt->_environ[i]; i++)
	{
		var_env = _strdup(curr_ctxt->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, curr_ctxt->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(curr_ctxt, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; curr_ctxt->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = curr_ctxt->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(curr_ctxt->_environ[k]);
	free(curr_ctxt->_environ);
	curr_ctxt->_environ = realloc_environ;
	return (1);
}

/**
 * isvalid_env - Checks if variable is an environment variable.
 *
 * @h: Head of linked list.
 * @in: command string.
 * @ctxt: current context.
 * Return: void
 */
void isvalid_env(vinfo **h, char *in, context *ctxt)
{
	int row, chr, j, val_len;
	char **_envr;

	_envr = ctxt->_environ;
	row = 0;
	while (_envr[row])
	{
		j = 1;
		chr = 0;
		while (_envr[row][chr])
		{
			if (_envr[row][chr] == '=')
			{
				val_len = _strlen(_envr[row] + chr + 1);
				add_vinfo(h, j, _envr[row] + chr + 1, val_len);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
			chr++;
		}
		row++;
	}

	j = 0;
	while (in[j])
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
		j++;
	}

	add_vinfo(h, j, NULL, 0);
}
