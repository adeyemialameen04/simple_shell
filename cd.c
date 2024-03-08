#include "main.h"
#include <string.h>
#include <libgen.h>

/**
 * _builtin_cd - Builtin cd.
 * @data: Data struct.
 * Return: None.
 */
void _builtin_cd(data_t *data);
void _builtin_cd(data_t *data)
{
	char *dir = data->argv[1];
	char prev_dir[PATH_MAX];
	char *oldpwd = getenv("OLDPWD");
	char *home = getenv("HOME");

	if (dir == NULL || strcmp(dir, "~") == 0)
	{
		dir = home;

		if (dir == NULL)
		{
			return;
		}
	}
	else if (strcmp(dir, "-") == 0)
	{
		getcwd(prev_dir, sizeof(prev_dir));
		if (oldpwd != NULL && strcmp(oldpwd, prev_dir) != 0)
		{
			if (chdir(oldpwd) == 0)
			{
				printf("/%s\n", basename(oldpwd));
				getcwd(prev_dir, sizeof(prev_dir));
				setenv("OLDPWD", getenv("PWD"), 1);
				setenv("PWD", prev_dir, 1);
			}
			else
			{
				perror("cd");
			}
		}
		else
		{
			_print(prev_dir, STDOUT_FILENO);
			_print("\n", STDOUT_FILENO);
		}
		return;
	}

	if (chdir(dir) != 0)
	{
		if (errno == EACCES || errno == EPERM)
		{
			_print("./hsh: 1: cd: can't cd to ", STDERR_FILENO);
			_print(dir, STDERR_FILENO);
			_print("\n", STDERR_FILENO);
		}
		else if (errno == ENOENT)
		{
			_print("./hsh: 1: cd: can't cd to ", STDERR_FILENO);
			_print(dir, STDERR_FILENO);
			_print("\n", STDERR_FILENO);
		}
		else
		{
			perror("cd");
		}
		return;
	}
	else
	{
		char new_dir[PATH_MAX];

		getcwd(new_dir, sizeof(new_dir));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", new_dir, 1);
	}
}
