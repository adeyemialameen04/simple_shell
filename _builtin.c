#include "main.h"

/**
 * _get_builtin_fn - Selects the correct function to perform the builtin.
 * @s: Command passed as an argument to the program.
 *
 * Return: Pointer to the function that corresponds to the command,
 *         or NULL if the operator is not one of the expected command.
 */
void (*_get_builtin_fn(char *s))(data_t *data)
{
	int i = 0;

	builtin_t builtins[] = {
		{"env", _builtin_printenv},
		{"setenv", _builtin_set_env},
		{"unsetenv", _builtin_unset_env},
		{"exit", _builtin_exit},
		{"cd", _builtin_cd},
		{NULL, NULL}};

	while (builtins[i].builtin_cmd != NULL)
	{
		if (s != NULL && _strcmp(builtins[i].builtin_cmd, s) == 0)
		{
			return (builtins[i].fn);
		}
		i++;
	}

	return (NULL);
}

/**
 * _builtin_set_env - A custom setenv function for my shell
 * @data: Struct data.
 * Return: None
 */
void _builtin_set_env(data_t *data)
{
	if (data->argv[1] == NULL || data->argv[2] == NULL ||
		*data->argv[1] == '\0' ||
		*data->argv[2] == '\0')
	{
		_print("setenv: Invalid arguments\n", STDERR_FILENO);
		return;
	}

	if (setenv(data->argv[1], data->argv[2], 1) != 0)
	{
		_print("setenv", STDERR_FILENO);
	}

	data->environ = environ;
}

/**
 * _builtin_unset_env - A custom unsetenv function for my shell
 * @data: Struct data.
 * Return: None
 */
void _builtin_unset_env(data_t *data)
{
	if (data->argv[1] == NULL || *data->argv[1] == '\0')
	{
		_print("unsetenv: Invalid arguments\n", STDERR_FILENO);
		return;
	}

	if (unsetenv(data->argv[1]) != 0)
	{
		_print("unsetenv", STDERR_FILENO);
	}

	data->environ = environ;
}

/**
 * _builtin_printenv - A custom function for my shell thats prints the
 *						environment variables
 * @data: Struct data.
 * Return: None
 */
void _builtin_printenv(data_t *data)
{
	unsigned int i = 0;

	while (data->environ[i])
	{
		_print(data->environ[i], STDOUT_FILENO);
		_print("\n", STDOUT_FILENO);
		i++;
	}
}

/**
 * _builtin_exit - A custom exit function for my shell
 *					Exits with status also
 * @data: Struct data.
 * Return: None
 */
void _builtin_exit(data_t *data)
{
	if (data->argv[1] != NULL)
	{
		if (data->argv[1][0] == '-' || !_is_num(data->argv[1]))
		{
			_print_exit_err(data);
			data->exit_status = 2;
		}
		else
		{
			data->exit_status = _atoi(data->argv[1]);

			_free_argv(data);
			if (data->cmds != NULL)
			{
				_free_cmds(data);
				data->cmds = NULL;
			}
			exit(data->exit_status);
		}
	}
	else
	{
		_free_argv(data);
		if (data->cmds != NULL)
		{
			_free_cmds(data);
			data->cmds = NULL;
		}
		exit(data->exit_status);
	}
}
