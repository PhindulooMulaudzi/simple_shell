#include "shell.h"

/**
 * sigint_handler - Handle crtl + c call
 * @sig: Signal handler
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n:) ", 5);
}

/**
 * free_ctxt - Free current context.
 *
 * @curr_ctxt: The current context to be freed.
 * Return: void.
 */
void free_ctxt(context *curr_ctxt)
{
	unsigned int i;

	for (i = 0; curr_ctxt->_environ[i]; i++)
	{
		free(curr_ctxt->_environ[i]);
	}

	free(curr_ctxt->_environ);
	free(curr_ctxt->pid);
}

/**
 * set_ctxt - Set current context.
 *
 * @curr_ctxt: Context
 * @argv: Argument vector.
 * Return: void.
 */
void set_ctxt(context *curr_ctxt, char **argv)
{
	unsigned int i;

	curr_ctxt->argv = argv;
	curr_ctxt->cmd = NULL;
	curr_ctxt->args = NULL;
	curr_ctxt->exit_code = 0;
	curr_ctxt->count = 1;

	for (i = 0; environ[i]; i++)
		;

	curr_ctxt->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		curr_ctxt->_environ[i] = _strdup(environ[i]);
	}

	curr_ctxt->_environ[i] = NULL;
	curr_ctxt->pid = itostr(getpid());
}

/**
 * main - Entry point.
 *
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	context curr_ctxt;
	(void) argc;

	signal(SIGINT, sigint_handler);
	set_ctxt(&curr_ctxt, argv);
	shell_loop(&curr_ctxt);
	free_ctxt(&curr_ctxt);
	if (curr_ctxt.exit_code < 0)
		return (255);
	return (curr_ctxt.exit_code);
}
