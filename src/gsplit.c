#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gart.h>

/**
 * __gsplit - split up a given string into tokens by a delimiter
 *
 * @str: the string to split into tokens
 * @delim: the delimiter
 * @size: the size of the token to generate
 *
 * Return: return a pointer to an array of the generated tokens
*/

char **__gsplit(char *str, const char *delim, int size)
{
	int i;
	char *token;
	char **tokens;

	token = strtok(str, delim);
	if (token == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "fatal: insufficient memory");
		/* TODO free malloc'd variables */

		exit(EXIT_FAILURE);
	}

	for (i = 0; token != NULL; i++)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;

	free(token);

	return (tokens);
}
