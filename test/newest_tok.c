#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

char *search_path(char *file)
{
	char *PATH = strdup(getenv("PATH"));
	char *dir = strtok(PATH, ":");
	char *full_path = malloc(256); /* Allocate memory for full path*/

	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, file);
		if (access(full_path, F_OK) == 0)
		{
			free(PATH);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(PATH);
	free(full_path);
	return (NULL);
}

int exec_command(char **argv)
{
	__pid_t pid = fork();
	int res;

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		char *full_path = search_path(argv[0]);
		if (full_path == NULL)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
			exit(EXIT_FAILURE);
		}
		res = execve(full_path, argv, NULL);

		if (res == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		while (1)
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				if (errno != EINTR)
					continue;
				perror("waitpid");
				return (-1);
			}
			break;
		}
	}

	return (0);
}
