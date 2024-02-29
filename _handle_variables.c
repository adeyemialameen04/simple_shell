#include "main.h"

/**
 * _handle_variables - Function to handle command variables .
 * @data: The data struct.
 * Return: none.
 */
void _handle_variables(data_t *data);
void _handle_variables(data_t *data)
{
	int i;

	for (i = 0; i < data->argc; i++)
	{
		if (data->argv[i][0] == '$')
		{
			/*Get the variable name by removing the '$'*/

			char *var_name = data->argv[i] + 1;
			char *new_value = NULL;

			/*Handle ?*/
			if (strcmp(var_name, "?") == 0)
			{
				char exit_status_str[10];

				sprintf(exit_status_str, "%d", data->exit_status);
				new_value = strdup(exit_status_str);
			}
			/*Special case for '$'*/
			else if (strcmp(var_name, "$") == 0)
			{
				char pid_str[10];

				sprintf(pid_str, "%d", getpid());
				new_value = strdup(pid_str);
			}
			else
			{
				char *var_value = getenv(var_name);

				/*Replace token with val if var exists*/
				if (var_value != NULL)
				{
					new_value = strdup(var_value);
				}
				else
				{
					new_value = _strdup("");
				}
			}

			if (new_value != NULL)
			{
				free(data->argv[i]);
				data->argv[i] = new_value;
			}
		}
	}
}
