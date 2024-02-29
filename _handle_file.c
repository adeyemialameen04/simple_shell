#include "main.h"

int handle_file(char **argv, data_t *data)
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
