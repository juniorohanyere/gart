#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"


/**
 * echo - sends data to the interface referenced by a given craft
 *
 * @craft: pointer to the craft to reference
 * @cast: pointer to the cast in which the data to send is meant for
 * @message: the data/string to send
 * @emoji: the state of the @cast at the moment of sending the data
 *
 * Return: return an integral position of the echo from __ecraft->echo
*/

int echo(craft_t *craft, char *message, char *emoji, cast_t *cast)
{
	int i;
	char *emoji_dup;
	echo_t **echo = NULL;
	ecraft_t *ecraft;

	if (craft == NULL)
	{
		/* __nullcraft(cast, buffer, emoji); */
	}
	else
	{
		ecraft = __ecraft;

		while (ecraft != NULL)
		{
			if (ecraft->craft == craft)
			{
				emoji_dup = strdup(emoji);
				echo = __echo(echo, cast, message, emoji_dup);
				ecraft->echo = __echo(ecraft->echo, cast,
					message, emoji_dup);

				__setinterf(ecraft->craft, echo);

				for (i = 0; ecraft->echo[i] != NULL; i++)
					;
				free((*echo)->message);
				free((*echo)->emoji);
				free(*echo);
				free(echo);

				free(emoji_dup);

				return (i - 1);
			}
			ecraft = ecraft->next;
		}
	}
}

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

	return (echo);
}

/**
 * __delecho - deletes/pops out all echo information stored in __ecraft for
 *	       a craft
 *
 * @echo: double pointer to all echo information for a craft
 *
 * Return: return nothing
*/

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
