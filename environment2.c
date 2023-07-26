#include "shell.h"

/**
 * replaced_cmd - Replaces string into variables.
 *
 * @head: Head of the linked list.
 * @cmd: command string.
 * @new_cmd: New command string (replaced).
 * @nlen: New length.
 * Return: Replaced string.
 */
char *replaced_cmd(vinfo **head, char *cmd, char *new_cmd, int nlen)
{
	vinfo *idx;
	int i, j, k;

	idx = *head;
	j = 0;
	for (i = 0; i < nlen; i++)
	{
		if (cmd[j] == '$')
		{
			if (!(idx->len_var) && !(idx->len_val))
			{
				new_cmd[i] = cmd[j];
				j++;
			}
			else if (idx->len_var && !(idx->len_val))
			{
				for (k = 0; k < idx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < idx->len_val; k++)
				{
					new_cmd[i] = idx->val[k];
					i++;
				}
				j += (idx->len_var);
				i--;
			}
			idx = idx->next;
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
 * @cmd: command string.
 * @curr_ctxt: current context.
 * Return: Replaced string.
 */
char *rep_var(char *cmd, context *curr_ctxt)
{
	vinfo *head, *idx;
	char *exit_code, *new_cmd;
	int olen, nlen;

	exit_code = itostr(curr_ctxt->exit_code);
	head = NULL;

	olen = check_vars(&head, cmd, exit_code, curr_ctxt);

	if (head == NULL)
	{
		free(exit_code);
		return (cmd);
	}

	idx = head;
	nlen = 0;

	while (idx != NULL)
	{
		nlen += (idx->len_val - idx->len_var);
		idx = idx->next;
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
