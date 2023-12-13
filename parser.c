#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

/**
 * __tokenise - splits up a string into tokens by a delimiter
 *
 * @str: the string to split into tokens
 * @delim: the delimiter
 * @size: the size of token to generate
 *	  is also the limit of tokens generatable [is that even a word? :)]
 *
 * Return: return a pointer to an array of the generated tokens
*/

char **__tokenise(char *str, const char *delim, int size)
{
	int i;
	char *token;
	char **tokens;

	tokens = malloc(sizeof(char *) * size);
	if (tokens == NULL)
	{
		dprintf(STDERR_FILENO, "fatal: insufficient memory");
		/* TODO: free malloc'ed variables */
		exit(EXIT_FAILURE);
	}

	token = strtok(str, delim);
	if (token == NULL)
		return (NULL);

	for (i = 0; token != NULL; i++)
	{
		tokens[i] = token;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;

	free(token);

	return (tokens);
}
