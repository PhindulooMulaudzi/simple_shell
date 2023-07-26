#include "shell.h"

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
