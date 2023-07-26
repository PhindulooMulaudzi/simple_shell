#include "shell.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n:) ", 5);
}

/**
 * free_ctxt - Free ctxt structure.
 *
 * @curr_ctxt: The ctxt structure to be freed.
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
 * set_ctxt - Initialize ctxt structure.
 *
 * @curr_ctxt: The ctxt structure to be initialized.
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
	curr_ctxt->pid = aux_itoa(getpid());
}

/**
 * main - Entry point of the program.
 *
 * @ac: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int ac, char **argv)
{
	context curr_ctxt;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_ctxt(&curr_ctxt, argv);
	shell_loop(&curr_ctxt);
	free_ctxt(&curr_ctxt);
	if (curr_ctxt.exit_code < 0)
		return (255);
	return (curr_ctxt.exit_code);
}
