#include <stdio.h>
#include <stdlib.h>
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
 * Return: return nothing
*/

void echo(craft_t *craft, char *buffer, char *emoji, cast_t *cast)
{
	echo_t *echo = NULL;
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
				ecraft->echo = __echo(ecraft->echo, cast,
					buffer, emoji);

					__setinterf(ecraft->craft, __echo(NULL, cast,
					buffer, emoji));

				return;
			}
			ecraft = ecraft->next;
		}
	}
}
