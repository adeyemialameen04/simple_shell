#include "main.h"

/**
 * _shell - The main shell function.
 * Return: The exit status off the last command.
 */
int _shell(int argc, char *argv[])
{
	data_t data = initialize_data_struct();

	if (argc > 1)

		handle_file(argv, &data);
	else
		shell_loop(&data);

	return (data.exit_status);
}

/**
 * sigint_handler - Function to handle ctrl + c signal.
 * @signo: The signal number.
 */
void sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		_print("\n$ ", STDOUT_FILENO);
		fflush(stdout);
	}
}
