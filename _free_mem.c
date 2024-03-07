#include "main.h"

/**
 * _free_argv - Free the elements inside argv and set to NULL.
 * @data: The data struct.
 * Return: none.
 */
void _free_argv(data_t *data)
{
	int i;

	if (data->argv != NULL)
	{
		for (i = 0; data->argv[i] != NULL; i++)
		{
			free(data->argv[i]);
			data->argv[i] = NULL;
		}
		free(data->argv);
		data->argv = NULL;
	}
}

/**
 * _clean - Function to free the data struct memory.
 * @data: The data struct.
 * Return: None.
 */
void _clean(data_t *data)
{
	_free_argv(data);

	_free_cmds(data);
	__free_alias(data);
}

/**
 * _free_cmds - Free the elements inside argv and set to NULL.
 * @data: The data struct.
 * Return: none.
 */
void _free_cmds(data_t *data)
{
	if (data->cmds != NULL)
	{
		int i = 0;

		for (i = 0; i < data->cmds_count; i++)
		{
			free(data->cmds[i]);
			data->cmds[i] = NULL;
		}

		free(data->cmds);
		data->cmds = NULL;
	}
}

/**
 * __free_alias - Free the elements inside argv and set to NULL.
 * @data: The data struct.
 * Return: none.
 */
void __free_alias(data_t *data)
{
	Alias *current = data->alias_list;
	Alias *next;

	while (current != NULL)
	{
		next = current->next;

		free(current->name);
		current->name = NULL;

		free(current->value);
		current->value = NULL;

		free(current);

		current = next;
	}

	data->alias_list = NULL;
}
