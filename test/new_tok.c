#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int exec_command(char **argv);
int exec_command(char **argv)
{
	__pid_t pid = fork();
	char *path_env;
	char *token;
	char *path_copy;

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		/*Try to execute with the given path*/
		int res = execve(argv[0], argv, NULL);

		/*If it fails, try to find the command in the PATH environment variable*/
		if (res == -1)
		{
			path_env = getenv("PATH");

			if (path_env == NULL)
			{
				perror("getenv");
				exit(EXIT_FAILURE);
			}

			path_copy = strdup(path_env);

			if (path_copy == NULL)
			{
				perror("strdup");
				exit(EXIT_FAILURE);
			}

			token = strtok(path_copy, ":");
			while (token != NULL)
			{
				char *full_path = malloc(strlen(token) + strlen(argv[0]) + 2);

				if (full_path == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}

				sprintf(full_path, "%s/%s", token, argv[0]);

				/*Try to execute with the constructed path*/
				execve(full_path, argv, NULL);

				/*Free the allocated memory*/
				free(full_path);

				/*Move to the next PATH directory*/
				token = strtok(NULL, ":");
			}

			/*If we reach here, execve has failed*/
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
