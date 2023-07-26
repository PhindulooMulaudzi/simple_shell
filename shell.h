#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct ctxt - A structure for the enviornment context
 * @argv: argument vector
 * @cmd: input command
 * @args: command args
 * @exit_code: exit_code of the shell
 * @count: line count
 * @_environ: environment variable
 * @pid: process identifier of the shell
 */
typedef struct ctxt
{
	char **argv;
	char *cmd;
	char **args;
	int exit_code;
	int count;
	char **_environ;
	char *pid;
} context;

/**
 * struct sep - single linked list
 * @separator: separator (; | &)
 * @next: next node
 * Description: linked list to store separators.
 */
typedef struct sep
{
	char separator;
	struct sep *next;
} separator;

/**
 * struct cin - single linked list
 * @line: command
 * @next: next node
 * Description: linked list to store command lines
 */
typedef struct cin
{
	char *line;
	struct cin *next;
} cmd_line;

/**
 * struct vlist - single linked list
 * @len_var: variable length
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: linked list to store variable info
 */
typedef struct vlist
{
	int len_var;
	char *val;
	int len_val;
	struct vlist *next;
} vinfo;

/**
 * struct bin - context struct for builtin command.
 * @name: Command name
 * @f: environment context
 */
typedef struct bin
{
	char *name;
	int (*f)(context *curr_ctxt);
} builtin;

separator *add_separator(separator **head, char sep);
void free_separator(separator **head);
cmd_line *add_cmd(cmd_line **head, char *line);
void free_cmd(cmd_line **head);

vinfo *add_vinfo(vinfo **head, int var_len, char *var, int val_len);
void free_vinfo(vinfo **head);

char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdptr(char **ptr, unsigned int old_size, unsigned int new_size);

char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

void rev_string(char *s);

int repeated_char(char *cmd, int i);
int error_sep_op(char *cmd, int i, char last);
int first_char(char *cmd, int *i);
void print_syntax_error(context *curr_ctxt, char *cmd, int i, int bool);
int check_syntax_error(context *curr_ctxt, char *cmd);

char *without_comment(char *in);
void shell_loop(context *curr_ctxt);

char *read_line(int *i_eof);

char *swap_char(char *cmd, int bool);
void add_nodes(separator **head_s, cmd_line **head_l, char *cmd);
void cmdnav_next(separator **list_s, cmd_line **list_l, context *curr_ctxt);
int split_commands(context *curr_ctxt, char *cmd);
char **split_line(char *cmd);

void isvalid_env(vinfo **h, char *in, context *ctxt);
int check_vars(vinfo **h, char *in, char *st, context *ctxt);
char *replaced_cmd(vinfo **head, char *cmd, char *new_cmd, int nlen);
char *rep_var(char *cmd, context *curr_ctxt);

void assign_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

int exec_line(context *curr_ctxt);

int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(context *curr_ctxt);
int check_error_cmd(char *dir, context *curr_ctxt);
int cmd_exec(context *curr_ctxt);

char *_getenv(const char *name, char **_environ);
int _env(context *curr_ctxt);

char *copy_info(char *name, char *value);
void set_env(char *name, char *value, context *curr_ctxt);
int _setenv(context *curr_ctxt);
int _unsetenv(context *curr_ctxt);

void cd_dot(context *curr_ctxt);
void cd_to(context *curr_ctxt);
void cd_previous(context *curr_ctxt);
void cd_to_home(context *curr_ctxt);

int cd_shell(context *curr_ctxt);

int (*get_context(char *cmd))(context *curr_ctxt);

int exit_shell(context *curr_ctxt);

int num_length(int n);
char *itostr(int n);
int _atoi(char *s);

char *strcat_cd(context *, char *, char *, char *);
char *error_get_cd(context *curr_ctxt);
char *error_not_found(context *curr_ctxt);
char *error_exit_shell(context *curr_ctxt);

char *error_get_alias(char **args);
char *error_env(context *curr_ctxt);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path(context *curr_ctxt);

int get_error(context *curr_ctxt, int eval);

void sigint_handler(int sig);

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help(void);
void help_exit(void);

void info_help(void);
void help_alias(void);
void help_cd(void);

int get_help(context *curr_ctxt);

#endif
