#include "shell.h"

/**
 * _memcpy - copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: void.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i = 0;

	while (i < size)
	{
		char_newptr[i] = char_ptr[i];
		i++;
	}
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: old ptr size, in bytes.
 * @new_size: new ptr size in bytes.
 *
 * Return: ptr.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;
	unsigned int i = 0;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
	{
		while (i < new_size)
		{
			((char *)newptr)[i] = ((char *)ptr)[i];
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < old_size)
		{
			((char *)newptr)[i] = ((char *)ptr)[i];
			i++;
		}
	}

	free(ptr);
	return (newptr);
}

/**
 * _reallocdptr - reallocatea memory for double pointer.
 * @ptr: double ptr.
 * @old_size: old ptr size, in bytes.
 * @new_size: new ptr size in bytes.
 *
 * Return: ptr.
 */
char **_reallocdptr(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i = 0;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	while (i < old_size)
	{
		newptr[i] = ptr[i];
		i++;
	}

	free(ptr);

	return (newptr);
}
