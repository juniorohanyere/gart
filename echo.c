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
 * @message: string action of @cast
 * @emoji: state of the cast at the moment
 *
 * Return: return a pointer to the generated echo information
*/

echo_t **__echo(echo_t **echo, cast_t *cast, char *message, char *emoji)
{
	int i;

	if (echo == NULL)
		echo = calloc(sizeof(echo_t *), 20);

	for (i = 0; echo[i] != NULL; i++)
			;

	/* update echo information */
	echo[i] = malloc(sizeof(echo_t));

	echo[i]->message = strdup(message);

	/* split emoji variable */

	echo[i]->emoji = __tokenise(emoji, "\t\r\n:", 4);
	echo[i]->cast = cast;

	//free(emoji);

	//__delcast((*temp)->cast);

	return (echo);
}

void __delecho(echo_t **echo)
{
	int i = 0, j = 0;

	if (echo == NULL)
		return;

	while (echo[i] != NULL)
	{
		free(echo[i]->message);

		free(echo[i]->emoji);

		__delcast(echo[i]->cast);

		free(echo[i]);

		i++;
	}

	free(echo);
}
