#include "main.h"

/**
 * add_alias - Adds or updates an alias in the alias list.
 * @data: The data struct.
 * @name: The name of the alias to add or update.
 * @value: The value associated with the alias.
 */
void add_alias(data_t *data, const char *name, const char *value)
{
	/*Check if the alias already exists*/
	Alias *existing_alias = find_alias(data, name);

	if (existing_alias)
	{
		/*Update the value of the existing alias*/
		free(existing_alias->value);
		existing_alias->value = strdup(value);
	}
	else
	{
		/*Create a new alias*/
		Alias *new_alias = malloc(sizeof(Alias));

		if (new_alias == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}

		new_alias->name = strdup(name);
		new_alias->value = strdup(value);
		new_alias->next = data->alias_list;
		data->alias_list = new_alias;
	}
}

/**
 * print_aliases_recursive - Prints all aliases in the alias list.
 * @current: The current alias.
 */
void print_aliases_recursive(Alias *current)
{
	if (current != NULL)
	{
		print_aliases_recursive(current->next);
		printf("%s='%s'\n", current->name, current->value);
	}
}

/**
 * print_aliases_reverse - Prints all aliases in the alias list.
 * @data: The data struct.
 */
void print_aliases_reverse(data_t *data)
{
	print_aliases_recursive(data->alias_list);
}

/**
 * find_alias - Finds an alias in the alias list.
 * @data: The data struct.
 * @name: The name of the alias to find.
 *
 * Return: Pointer to the found alias, or NULL if not found.
 */
Alias *find_alias(data_t *data, const char *name)
{
	Alias *current = data->alias_list;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * handle_alias_command - Handles the 'alias' shell command.
 * @data: The data struct.
 *
 * Description: Parses and processes arguments for alias command,
 * adding, updating, or printing aliases based on the arguments.
 */
void handle_alias_command(data_t *data);
void handle_alias_command(data_t *data)
{
	int i;

	/* Check if any arguments are provided */
	if (data->argc == 1)
	{
		print_aliases_reverse(data);
		return;
	}

	/* Loop through each argument */
	for (i = 1; i < data->argc; i++)
	{
		char *arg = data->argv[i];

		/* Check if argument contains an assignment (alias='value') */
		char *equal_sign = strchr(arg, '=');

		if (equal_sign)
		{
			/* Extract name and value */
			char *name = strndup(arg, equal_sign - arg);
			char *value;

			/* Check if there is a value after the equals sign */
			if (equal_sign + 1 < arg + strlen(arg))
			{
				value = strdup(equal_sign + 1);
			}
			else
			{
				/* Handle case where there is no value after the equals sign */
				fprintf(stderr, "alias: %s: value missing\n", name);
				free(name);
				continue;
			}

			/* Add alias */
			add_alias(data, name, value);

			free(name);
			free(value);
		}
		else
		{
			/* Find and print existing alias */
			Alias *alias = find_alias(data, arg);

			if (alias)
			{
				printf("%s='%s'\n", alias->name, alias->value);
			}
			else
			{
				/* Handle non-existent alias */
				printf("alias: %s: not found\n", arg);
			}
		}
	}
}

/**
 * substitute_aliases - Substitutes aliases in the command.
 * @data: The data struct.
 */
void substitute_aliases(data_t *data)
{
	int i;

	if (data->argv == NULL)
		return;

	for (i = 0; data->argv[i] != NULL; i++)
	{
		Alias *alias = find_alias(data, data->argv[i]);

		if (alias != NULL)
		{
			if (data->argv[i] != NULL)
			{
				free(data->argv[i]);
				data->argv[i] = strdup(alias->value);

				substitute_aliases(data);
			}
		}
	}
}
