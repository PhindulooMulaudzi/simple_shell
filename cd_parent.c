#include "shell.h"

/**
 * set_oldpwd - helper to the cd dot method.
 *
 * @curr_ctxt: ctxt relevant (environ).
 *
 * Return: void
 */
void set_oldpwd(context *curr_ctxt) {
    char pwd[PATH_MAX];
    char *cp_pwd;

    getcwd(pwd, sizeof(pwd));
    cp_pwd = _strdup(pwd);
    set_env("OLDPWD", cp_pwd, curr_ctxt);
    free(cp_pwd);
}

/**
 * update_pwd - helper to the cd dot method.
 *
 * @curr_ctxt: ctxt relevant (environ).
 *
 * Return: void
 */
void update_pwd(char *new_pwd, context *curr_ctxt) {
    chdir(new_pwd);
    set_env("PWD", new_pwd, curr_ctxt);
}

/**
 * cd_dot - Changes to the parent directory.
 *
 * @curr_ctxt: ctxt relevant (environ).
 *
 * Return: void
 */
void cd_dot(context *curr_ctxt) {
    char pwd[PATH_MAX];
    char *dir, *cp_pwd, *cp_strtok_pwd;

    getcwd(pwd, sizeof(pwd));
    dir = curr_ctxt->args[1];

    if (_strcmp(".", dir) == 0) {
        set_oldpwd(curr_ctxt);
        return;
    }

    if (_strcmp("/", pwd) == 0)
        return;

    cp_pwd = _strdup(pwd);
    cp_strtok_pwd = cp_pwd;
    rev_string(cp_strtok_pwd);
    cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");

    while (cp_strtok_pwd != NULL) {
        cp_strtok_pwd = _strtok(NULL, "\0");
        if (cp_strtok_pwd != NULL)
            rev_string(cp_strtok_pwd);
    }

    if (cp_strtok_pwd != NULL)
        update_pwd(cp_strtok_pwd, curr_ctxt);
    else
        update_pwd("/", curr_ctxt);

    free(cp_pwd);
    curr_ctxt->exit_code = 0;
}
