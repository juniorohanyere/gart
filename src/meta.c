#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ecraft.h"

/**
 * __addmeta - generates and update meta information for a craft
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
	int i = 0, meta_size, size = 4;	/* 4 bytes */

	if (meta == NULL)
	{
		meta_size = size * (2 * i + 3);
		meta = calloc(sizeof(meta_t *), meta_size);
		if (meta == NULL)
			return (NULL);
	}

	for (i = 0; meta[i] != NULL; i++)
		;

	meta_size = size * (2 * i + 3);	/* cool formula */
	meta = realloc(meta, sizeof(meta_t *) * meta_size);
	if (meta == NULL)
		return (NULL);

	/*
	 * Original Formula/Algorithm: (i + size + (i - 1)) * size
	 * By: Junior Ohanyere <junohanyere@gmail.com>
	 *
	 * History: (i + size + (i - 1)) * size)
	 *
	 *	    (i * size * 2) + (size * size) - size
	 *
	 *	    size * (2 * i + 3)	simplified
	 *
	 * Where size = 4 bytes represented by 4 int
	*/

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
