#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ecraft.h"

/**
 * stage - sends data to the interface referenced by a given craft
 *
 * @craft: pointer to the craft to reference
 * @cast: pointer to the cast in which the data to send is meant for
 * @message: the data/string to send
 * @emoji: the state of the @cast at the moment of sending the data
 *
 * Return: return an integral position of the message to echo from
 *	   __ecraft->meta
*/

int stage(craft_t *craft, char *message, char *emoji, cast_t *cast)
{
	int i;
	char *emoji_dup;
	meta_t **meta = NULL;
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
				meta = __meta(meta, cast, message, emoji_dup);
				ecraft->meta = __meta(ecraft->meta, cast,
					message, emoji_dup);

				__setinterf(ecraft->craft, meta);

				for (i = 0; ecraft->meta[i] != NULL; i++)
					;
				free((*meta)->message);
				free((*meta)->emoji);
				free(*meta);
				free(meta);

				free(emoji_dup);

				return (i - 1);
			}
			ecraft = ecraft->next;
		}
	}
}
