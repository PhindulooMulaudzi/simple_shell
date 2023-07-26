#include "shell.h"

/**
 * assign_line - assigns the line var for get_line
 * @lineptr: Buffer to store cmd str
 * @buffer: string to be assigned
 * @n: line size
 * @j: bud size
 */
void assign_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Get inpt from stream
 * @lineptr: buffer
 * @n: size
 * @stream: stream to read from
 * Return: number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t cmd;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (cmd == 0)
		fflush(stream);
	else
		return (-1);
	cmd = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && cmd == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && cmd != 0)
		{
			cmd++;
			break;
		}
		if (cmd >= BUFSIZE)
			buffer = _realloc(buffer, cmd, cmd + 1);
		buffer[cmd] = t;
		cmd++;
	}
	buffer[cmd] = '\0';
	assign_line(lineptr, n, buffer, cmd);
	retval = cmd;
	if (i != 0)
		cmd = 0;
	return (retval);
}

/**
 * read_line - Read the command string from stdin.
 *
 * @i_eof: Return value of the getline function.
 * Return: The command string.
 */
char *read_line(int *i_eof)
{
	char *cmd = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&cmd, &bufsize, stdin);

	return (cmd);
}
