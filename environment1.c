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
