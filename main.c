#include "main.h"

#define MOVE_LEFT "\033[D"
#define MOVE_RIGHT "\033[C"

/**
 * main - Entry point to my shell program.
 * @argc: Arguments count.
 * @argv: Argument variables(vectors).
 * Return: Exit status.
 */
int main(int argc, char *argv[])
{

	return (_shell(argc, argv));
}
