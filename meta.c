#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ecraft.h"

/**
 * __meta - generates and update meta information for a craft
 *
 * @meta: pointer to the head meta
 * @cast: the cast of a craft
 * @buffer: string action of @cast
 * @emoji: state of the cast at the moment
 *
 * Return: return a pointer to the generated meta information
*/

meta_t *__meta(meta_t *meta, cast_t *cast, char *buffer, char *emoji)
{
	meta_t *temp, *tmp;

	temp = malloc(sizeof(meta_t));
	if (temp == NULL)
	{
		dprintf(STDERR_FILENO, "fatal: insufficient memory\n");
		/* TODO: free malloc'ed variables */
		exit(EXIT_FAILURE);
	}

	temp->body = strdup(buffer);

	/* split emoji variable */
	temp->emoji = __tokenise(strdup(emoji), ":");

	temp->cast = cast;
	temp->next = NULL;

	/*
	 * update and arrange meta information ground to head from earliest to
	 * oldest
	*/
	meta = __mupdate(meta, temp);

	return (meta);
}
