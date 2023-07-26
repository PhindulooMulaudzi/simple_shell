#include "shell.h"

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
