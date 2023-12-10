#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

/**
 * __meta - generate meta information for a craft
 *
 * @cast: the cast of a craft
 * @buffer: string action of @cast
 * @emoji: state of the cast at the moment
 *
 * Return: return a pointer to the generated meta information
*/

meta_t *__meta(cast_t *cast, char *buffer, char *emoji)
{
	meta_t *meta;

	meta = malloc(sizeof(meta_t));
	if (meta == NULL)
	{
		dprintf(STDERR_FILENO, "fatal: insufficient memory\n");
		/* TODO: free malloc'ed variables */
		exit(EXIT_FAILURE);
	}

	meta->body = strdup(buffer);

	/* split state variable */
	meta->emoji = __tokenise(emoji, ":");

	meta->cast = cast;
	meta->next = NULL;

	return (meta);
}
