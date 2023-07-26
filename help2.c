#include "shell.h"

/**
 * info_help - Display info for the command 'help' command.
 * Return: void
 */
void info_help(void)
{
	char *helpMsg = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
	helpMsg = "\tDisplay information about available commands.\n ";
	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
	helpMsg = "Displays summaries of commands.\n";
	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
}

/**
 * help_alias - Display info for the 'alias' command.
 * Return: void
 */
void help_alias(void)
{
	char *helpMsg = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
	helpMsg = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
}

/**
 * help_cd - Display info for the command 'cd' command.
 * Return: void
 */
void help_cd(void)
{
	char *helpMsg = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
	helpMsg = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, helpMsg, _strlen(helpMsg));
}


/**
 * get_help - function that retrieves help messages according context
 * @curr_ctxt: current context (args and cmd)
 * Return: Return 0
*/
int get_help(context *curr_ctxt)
{

	if (curr_ctxt->args[1] == 0)
		help();
	else if (_strcmp(curr_ctxt->args[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(curr_ctxt->args[1], "env") == 0)
		help_env();
	else if (_strcmp(curr_ctxt->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(curr_ctxt->args[1], "help") == 0)
		info_help();
	else if (_strcmp(curr_ctxt->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(curr_ctxt->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(curr_ctxt->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, curr_ctxt->args[0],
		      _strlen(curr_ctxt->args[0]));

	curr_ctxt->exit_code = 0;
	return (1);
}

