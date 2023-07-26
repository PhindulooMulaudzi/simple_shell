#include "shell.h"

/**
 * add_separator - Adds a separator.
 * @head: head address.
 * @sep: separator.
 * Return: ptr to the head.
 */
separator *add_separator(separator **head, char sep)
{
	separator *new, *temp;

	new = malloc(sizeof(separator));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_separator - Frees a separator.
 * @head: head address.
 * Return: void
 */
void free_separator(separator **head)
{
	separator *temp, *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_cmd - Appends a cmd to cmd_line.
 * @head: head address.
 * @line: Command line.
 * Return: ptr to the head.
 */
cmd_line *add_cmd(cmd_line **head, char *line)
{
	cmd_line *new, *temp;

	new = malloc(sizeof(cmd_line));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_cmd - Frees a cmd_line.
 * @head: head address.
 * Return: void
 */
void free_cmd(cmd_line **head)
{
	cmd_line *temp, *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}


/**
 * add_vinfo - Adds a variable at the end of a vinfo list.
 * @head: head address.
 * @var_len: variable length.
 * @val: var value.
 * @val_len: value length.
 * Return: ptr to the head.
 */
vinfo *add_vinfo(vinfo **head, int var_len, char *val, int val_len)
{
	vinfo *new_node, *temp;

	new_node = malloc(sizeof(vinfo));
	if (new_node == NULL)
		return (NULL);

	new_node->len_var = var_len;
	new_node->val = val;
	new_node->len_val = val_len;

	new_node->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_node;
	}
	else
	{
		for (; temp->next != NULL; temp = temp->next)
			;
		temp->next = new_node;
	}

	return (*head);
}

/**
 * free_vinfo - Frees a vinfo list.
 * @head: head address.
 * Return: void
 */
void free_vinfo(vinfo **head)
{
	vinfo *temp;
	vinfo *curr;

	if (head != NULL && *head != NULL)
	{
		curr = *head;
		for (; (temp = curr) != NULL; )
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
