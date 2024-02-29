#include "main.h"

/**
 * _print_not_found - Print err when a command is not found.
 * @data: The data struct.
 * Return: None.
 */
void _print_not_found(data_t *data)
{
	char *err_msg = "./hsh: 1: ";
	char *not_found = ": not found\n";

	_print(err_msg, STDERR_FILENO);
	_print(data->argv[0], STDERR_FILENO);
	_print(not_found, STDERR_FILENO);
}

/**
 * _print_exit_err - Print err when an illegal number is passed to
 *						the exit status is not found.
 * @data: The data struct.
 * Return: None.
 */
void _print_exit_err(data_t *data)
{
	char *err_msg = "./hsh: 1: ";
	char *illegal_num = "exit: Illegal number: ";

	_print(err_msg, STDERR_FILENO);
	_print(illegal_num, STDERR_FILENO);
	_print(data->argv[1], STDERR_FILENO);
	_print("\n", STDERR_FILENO);
}

/**
 * _print_file_not_found_err - Print error when a file passed
 *								as argv is not found.
 * @argv: Argument variables(vectors).
 * Return:None.
 */
void _print_file_not_found_err(char *argv[])
{
	char *err_msg = "./hsh: 0: ";
	char *cant_open = "Can't open ";

	_print(err_msg, STDERR_FILENO);
	_print(cant_open, STDERR_FILENO);
	_print(argv[1], STDERR_FILENO);
	_print("\n", STDERR_FILENO);
}
