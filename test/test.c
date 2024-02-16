#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "main.h"

int main(void);
int main(void)
{
	int argc = 0;
	char **argv = NULL;
	char *cmd = NULL;
	ssize_t read;
	size_t n = 0;

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			printf("$ ");
			read = getline(&cmd, &n, stdin);
			if (read == -1)
			{
				if (errno != 0)
					perror("getline");
				break;
			}

			tokenize_command(cmd, &argc, &argv);

			if (strcmp(argv[0], "exit") == 0)
				break;

			if (exec_command(argv) == -1)
			{
				fprintf(stderr, "Failed to execute your command boss\n");
			}
		}
	}
	else
	{
		while ((read = getline(&cmd, &n, stdin)) != -1)
		{
			tokenize_command(cmd, &argc, &argv);
			if (exec_command(argv) == -1)
			{
				fprintf(stderr, "Failed to execute your command boss\n");
			}
		}
		exit(EXIT_SUCCESS);
	}

	free(cmd);
	free(argv);
	return (0);
}
