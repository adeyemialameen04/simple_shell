#include "main.h"

ssize_t _read_line(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t read = getline(lineptr, n, stream);

	if (read == -1)
		perror("custom getline");

	return (read);
}
