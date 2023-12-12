#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

__ECRAFT;	/* by-pass betty error for use of global variables */

/**
 * pushc - sends data to the interface referenced by a given craft
 *
 * @craft: pointer to the craft to reference
 * @cast: pointer to the cast in which the data to send is meant for
 * @buffer: the data/string to send
 * @emoji: the state of the @cast at the moment of sending the data
 *
 * Return: return an integral position of the echo from __ecraft->echo
*/

int echo(craft_t *craft, char *buffer, char *emoji, cast_t *cast)
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
				echo = __echo(echo, cast, buffer, emoji_dup);
				ecraft->echo = __echo(ecraft->echo, cast,
					buffer, emoji_dup);

				__setinterf(ecraft->craft, echo);

				for (i = 0; ecraft->echo[i] != NULL; i++)
					;
				free((*echo)->message);
				free((*echo)->emoji);
				//__delcast((*echo)->cast);
				free(*echo);
				free(echo);

				free(emoji_dup);

				return (i - 1);
			}
			ecraft = ecraft->next;
		}
	}
}

void freecraft(void)
{
	ecraft_t *ecraft = __ecraft, *next;

	if (__ecraft == NULL)
		return;

	while (ecraft != NULL)
	{
		next = ecraft->next;

		endcraft(ecraft->craft);
		__delecho(ecraft->echo);
		free(ecraft);

		ecraft = next;
	}
}
