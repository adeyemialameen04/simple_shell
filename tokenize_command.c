#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void tokenize_command(char *cmd, int *argc, char ***argv)
{
	char *cmd_copy;
	char *delim = " \n";
	char *token;
	int i = 0;

	cmd[strcspn(cmd, "\n")] = '\0';
	cmd_copy = strdup(cmd);
	if (cmd_copy == NULL)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(cmd_copy, delim);
	*argc = 0;

	/* Counting argc */
	while (token)
	{
		(*argc)++;
		token = strtok(NULL, delim);
	}

	free(cmd_copy);

	*argv = calloc((*argc + 1), sizeof(char *));
	if (*argv == NULL)
	{
		perror("calloc failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(cmd, delim);

	while (token)
	{
		(*argv)[i] = token;
		i++;
		token = strtok(NULL, delim);
	}

	(*argv)[i] = NULL;
}
