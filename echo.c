#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

/**
 * __echo - generates and update echo information for a craft
 *
 * @echo: pointer to the head echo
 * @cast: the cast of a craft
 * @buffer: string action of @cast
 * @emoji: state of the cast at the moment
 *
 * Return: return a pointer to the generated echo information
*/

echo_t **__echo(echo_t **echo, cast_t *cast, char *buffer, char *emoji)
{
	int i;
	echo_t **temp;

	temp = malloc(sizeof(echo_t *));
	(*temp) = malloc(sizeof(echo_t));

	if (temp == NULL || (*temp) == NULL)
	{
		dprintf(STDERR_FILENO, "fatal: insufficient memory\n");
		/* TODO: free malloc'ed variables */
		exit(EXIT_FAILURE);
	}

	(*temp)->body = strdup(buffer);

	/* split emoji variable */
	(*temp)->emoji = __tokenise(strdup(emoji), " \t\r\n:", 4);

	(*temp)->cast = cast;

	if (echo == NULL)
		return (temp);

	/* update echo information */
	for (i = 0; echo[i] != NULL; i++)
		;

	echo[i] = *temp;

	return (echo);
}
