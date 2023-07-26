#include "shell.h"

int cmp_env_name(const char *nenv, const char *name)
{
    int i;

    for (i = 0; nenv[i] != '='; i++)
    {
        if (nenv[i] != name[i])
        {
            return (0);
        }
    }

    return (i + 1);
}

char *_getenv(const char *name, char **_environ)
{
    char *ptr_env;
    int i, mov;

    ptr_env = NULL;
    mov = 0;

    for (i = 0; _environ[i]; i++)
    {
        mov = cmp_env_name(_environ[i], name);
        if (mov)
        {
            ptr_env = _environ[i];
            break;
        }
    }

    return (ptr_env + mov);
}

int _env(context *curr_ctxt)
{
    int i, j;

    for (i = 0; curr_ctxt->_environ[i]; i++)
    {
        for (j = 0; curr_ctxt->_environ[i][j]; j++)
        {
            write(STDOUT_FILENO, &curr_ctxt->_environ[i][j], 1);
        }

        write(STDOUT_FILENO, "\n", 1);
    }

    curr_ctxt->exit_code = 0;
    return (1);
}


/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @curr_ctxt: ctxt structure (environ)
 * Return: no return
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

	curr_ctxt->_environ = _reallocdp(curr_ctxt->_environ, i, sizeof(char *) * (i + 2));
	curr_ctxt->_environ[i] = copy_info(name, value);
	curr_ctxt->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @curr_ctxt: ctxt relevant (env name and env value)
 *
 * Return: 1 on success.
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
 * _unsetenv - deletes a environment variable
 *
 * @curr_ctxt: ctxt relevant (env name)
 *
 * Return: 1 on success.
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
 * check_env - Checks if the typed variable is an environment variable.
 *
 * @h: Head of linked list.
 * @in: cmd string.
 * @ctxt: ctxt structure.
 * Return: void
 */
void check_env(vinfo **h, char *in, context *ctxt)
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

/**
 * check_vars - Checks if the typed variable is $$ or $?.
 *
 * @h: Head of the linked list.
 * @in: cmd string.
 * @st: Last exit_code of the Shell.
 * @ctxt: ctxt structure.
 * Return: void
 */
int check_vars(vinfo **h, char *in, char *st, context *ctxt)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(ctxt->pid);

	i = 0;
	while (in[i])
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_vinfo(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_vinfo(h, 2, ctxt->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_vinfo(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_vinfo(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_vinfo(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_vinfo(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_vinfo(h, 0, NULL, 0);
			else
				check_env(h, in + i, ctxt);
		}
		i++;
	}

	return (i);
}

/**
 * replaced_cmd - Replaces string into variables.
 *
 * @head: Head of the linked list.
 * @cmd: cmd string.
 * @new_cmd: New cmd string (replaced).
 * @nlen: New length.
 * Return: Replaced string.
 */
char *replaced_cmd(vinfo **head, char *cmd, char *new_cmd, int nlen)
{
	vinfo *indx;
	int i, j, k;

	indx = *head;
	j = 0;
	for (i = 0; i < nlen; i++)
	{
		if (cmd[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_cmd[i] = cmd[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_cmd[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_cmd[i] = cmd[j];
			j++;
		}
	}

	return (new_cmd);
}

/**
 * rep_var - Calls functions to replace string into vars.
 *
 * @cmd: cmd string.
 * @curr_ctxt: ctxt structure.
 * Return: Replaced string.
 */
char *rep_var(char *cmd, context *curr_ctxt)
{
	vinfo *head, *indx;
	char *exit_code, *new_cmd;
	int olen, nlen;

	exit_code = aux_itoa(curr_ctxt->exit_code);
	head = NULL;

	olen = check_vars(&head, cmd, exit_code, curr_ctxt);

	if (head == NULL)
	{
		free(exit_code);
		return (cmd);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_cmd = malloc(sizeof(char) * (nlen + 1));
	new_cmd[nlen] = '\0';

	new_cmd = replaced_cmd(&head, cmd, new_cmd, nlen);

	free(cmd);
	free(exit_code);
	free_vinfo(&head);

	return (new_cmd);
}
