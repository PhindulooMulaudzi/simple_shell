#include "shell.h"

/**
 * help_env - Displays info for the command 'env'.
 * Return: void.
 */
void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Display the shell's environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_setenv - Displays info for the command 'setenv'.
 * Return: void.
 */
void help_setenv(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Incorporate a new definition into the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_unsetenv - Displays info for the command 'unsetenv'.
 * Return: void.
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Completely remove an entry from the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help - Entry point for 'help'.
 * Return: void.
 */
void help(void)
{
	char *help = ":) bash, beta-release\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "The following commands are defined. To view list, type 'help'.";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "For  additional information about the command 'name', type 'help name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_exit - Displays info for the command 'exit'.
 * Return: void.
 */
void help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a exit_code of N. If N is omitted, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "exit_code is that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
