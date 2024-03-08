#include "main.h"

void _builtin_cd(data_t *data)
{
	char *new_dir;

	if (data->argc > 2)
	{
		_print("cd: too many arguments\n", STDOUT_FILENO);
		return;
	}

	new_dir = (data->argc == 1) ? getenv("HOME") : data->argv[1];

	if (new_dir == NULL)
	{
		perror("cd");
		return;
	}

	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return;
	}

	update_pwd(new_dir);
}

void update_pwd(char *new_dir)
{
	char cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", new_dir, 1);
	}
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
}
