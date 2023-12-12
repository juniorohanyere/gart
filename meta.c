#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"


/**
 * surge - sends data to the interface referenced by a given craft
 *
 * @craft: pointer to the craft to reference
 * @cast: pointer to the cast in which the data to send is meant for
 * @message: the data/string to send
 * @emoji: the state of the @cast at the moment of sending the data
 *
 * Return: return an integral position of the message to echo from
 *	   __ecraft->meta
*/

int surge(craft_t *craft, char *message, char *emoji, cast_t *cast)
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

/**
 * __meta - generates and update meta information for a craft
 *
 * @meta: pointer to the head metadata
 * @cast: the cast of a craft
 * @message: string action of @cast
 * @emoji: state of the cast at the moment
 *
 * Return: return a pointer to the generated meta information
*/

meta_t **__meta(meta_t **meta, cast_t *cast, char *message, char *emoji)
{
	int i;

	if (meta == NULL)
		meta = calloc(sizeof(meta_t *), 20);

	for (i = 0; meta[i] != NULL; i++)
		;

	/* update meta information */
	meta[i] = malloc(sizeof(meta_t));

	meta[i]->message = strdup(message);

	/* split emoji variable */

	meta[i]->emoji = __tokenise(emoji, "\t\r\n:", 4);
	meta[i]->cast = cast;

	return (meta);
}

/**
 * __delmeta - deletes/pops out all meta information stored in __ecraft for
 *	       a craft
 *
 * @meta: double pointer to all meta information for a craft
 *
 * Return: return nothing
*/

void __delmeta(meta_t **meta)
{
	int i = 0, j = 0;

	if (meta == NULL)
		return;

	while (meta[i] != NULL)
	{
		free(meta[i]->message);

		free(meta[i]->emoji);

		__delcast(meta[i]->cast);

		free(meta[i]);

		i++;
	}

	free(meta);
}
