#include "shell.h"

/**
 * get_context - context that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the context command
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
