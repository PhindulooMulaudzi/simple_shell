#include "shell.h"

/**
 * cmd_exec - Execute command from given context
 *
 * @curr_ctxt: Relevant context.
 * Return: 1.
 */
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
