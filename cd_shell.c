#include "shell.h"

/**
 * cd_shell - Changes current directory.
 *
 * @curr_ctxt: ctxt relevant.
 * Return: 1 on success.
 */
int cd_shell(context *curr_ctxt)
{
	char *dir;
	int is_home, is_home2, is_ddash;

	dir = curr_ctxt->args[1];

	if (dir != NULL)
	{
		is_home = _strcmp("$HOME", dir);
		is_home2 = _strcmp("~", dir);
		is_ddash = _strcmp("--", dir);
	}

	if (dir == NULL || !is_home || !is_home2 || !is_ddash)
	{
		cd_to_home(curr_ctxt);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(curr_ctxt);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(curr_ctxt);
		return (1);
	}

	cd_to(curr_ctxt);

	return (1);
}


/**
 * cd_dot - Changes to the parent directory.
 *
 * @curr_ctxt: ctxt relevant (environ).
 *
 * Return: void
 */
void cd_dot(context *curr_ctxt)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, curr_ctxt);
	dir = curr_ctxt->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, curr_ctxt);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");

	while (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}

	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, curr_ctxt);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", curr_ctxt);
	}

	curr_ctxt->exit_code = 0;
	free(cp_pwd);
}

/**
 * cd_to - Changes to a directory given by the user.
 *
 * @curr_ctxt: ctxt relevant (directories).
 * Return: void
 */
void cd_to(context *curr_ctxt)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = curr_ctxt->args[1];
	if (chdir(dir) == -1)
	{
		get_error(curr_ctxt, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, curr_ctxt);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, curr_ctxt);

	free(cp_pwd);
	free(cp_dir);

	curr_ctxt->exit_code = 0;

	chdir(dir);
}

/**
 * cd_previous - Changes to the previous directory.
 *
 * @curr_ctxt: ctxt relevant (environ).
 * Return: void
 */
void cd_previous(context *curr_ctxt)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", curr_ctxt->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, curr_ctxt);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, curr_ctxt);
	else
		set_env("PWD", cp_oldpwd, curr_ctxt);

	p_pwd = _getenv("PWD", curr_ctxt->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	curr_ctxt->exit_code = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - Changes to the home directory.
 *
 * @curr_ctxt: ctxt relevant (environ).
 * Return: void
 */
void cd_to_home(context *curr_ctxt)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", curr_ctxt->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, curr_ctxt);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(curr_ctxt, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, curr_ctxt);
	set_env("PWD", home, curr_ctxt);
	free(p_pwd);
	curr_ctxt->exit_code = 0;
}
