#include "shell.h"

/**
 * without_comment - deletes comments from the cmd
 *
 * @in: command string
 * Return: cmd without comments
 */
char *without_comment(char *in)
{
	int i = 0, up_to = 0;

	while (in[i])
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
		i++;
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shell
 * @curr_ctxt: ctxt relevant (argv, cmd, args)
 *
 * Return: void.
 */
void shell_loop(context *curr_ctxt)
{
	int loop = 1, i_eof;
	char *cmd;

	while (loop == 1)
	{
		write(STDIN_FILENO, ":) ", 4);
		cmd = read_line(&i_eof);
		if (i_eof != -1)
		{
			cmd = without_comment(cmd);
			if (cmd == NULL)
				continue;

			if (check_syntax_error(curr_ctxt, cmd) == 1)
			{
				curr_ctxt->exit_code = 2;
				free(cmd);
				continue;
			}
			cmd = rep_var(cmd, curr_ctxt);
			loop = split_commands(curr_ctxt, cmd);
			curr_ctxt->count += 1;
			free(cmd);
		}
		else
		{
			loop = 0;
			free(cmd);
		}
	}
}
