#include "main.h"

/**
 * _handle_file - Function to handle file being passed as argument.
 * @argv: Argument variables(vectors).
 * @data: The data struct.
 * Return: 1 on failure and 0 on success.
 */
int _handle_file(char **argv, data_t *data)
{
	FILE *fd;
	char *lineptr = NULL;
	size_t n = 0;

	fd = fopen(argv[1], "r");
	if (fd == NULL)
	{
		_print_file_not_found_err(argv);
		data->exit_status = 127;
		return (1);
	}

	while (getline(&lineptr, &n, fd) != -1)
	{
		data->cmd = lineptr;

		_tokenize_command(data, " \n");
		execute_cmd(data);

		_free_cmds(data);
		_free_argv(data);
	}
	free(lineptr);
	fclose(fd);

	return (0);
}
