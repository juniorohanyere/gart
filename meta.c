#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"

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

meta_t **__addmeta(meta_t **meta, cast_t *cast, char *message, char *emoji)
{
	int i, craft_size = __ec_size;

	assert(craft_size >= 1024);

	if (meta == NULL)
		meta = calloc(sizeof(meta_t *), __ec_size);

	for (i = 0; meta[i] != NULL; i++)
		;

	/* update meta information */
	meta[i] = malloc(sizeof(meta_t));

	meta[i]->message = strdup(message);

	/* split emoji variable */

	meta[i]->emoji = __tokenise(emoji, " \t\r\n:", 4);
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

		free(meta[i]);

		i++;
	}

	free(meta);
}
