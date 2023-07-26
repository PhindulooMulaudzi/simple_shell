#include "shell.h"

/**
 * add_nodes - Add separators note to command lines
 *
 * @head_s: separator head
 * @head_l: comand line head
 * @cmd: command string
 * Return: void
 */
void add_nodes(separator **head_s, cmd_line **head_l, char *cmd)
{
	int i;
	char *line;

	cmd = swap_char(cmd, 0);

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';')
			add_separator(head_s, cmd[i]);

		if (cmd[i] == '|' || cmd[i] == '&')
		{
			add_separator(head_s, cmd[i]);
			i++;
		}
		i++;
	}

	line = _strtok(cmd, ";|&");
	do {
		line = swap_char(line, 1);
		add_cmd(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * cmdnav_next - Goes to the next command line stored
 *
 * @list_s: Separator list
 * @list_l: Command line list
 * @curr_ctxt: current context
 * Return: void
 */
void cmdnav_next(separator **list_s, cmd_line **list_l, context *curr_ctxt)
{
	int loop_sep;
	separator *ls_s;
	cmd_line *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (curr_ctxt->exit_code == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - Splits command lines
 *
 * @curr_ctxt: current context
 * @cmd: command string
 * Return: 0 or 1
 */
int split_commands(context *curr_ctxt, char *cmd)
{
	separator *head_s, *list_s;
	cmd_line *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, cmd);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		curr_ctxt->cmd = list_l->line;
		curr_ctxt->args = split_line(curr_ctxt->cmd);
		loop = exec_line(curr_ctxt);
		free(curr_ctxt->args);

		if (loop == 0)
			break;

		cmdnav_next(&list_s, &list_l, curr_ctxt);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_separator(&head_s);
	free_cmd(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}
