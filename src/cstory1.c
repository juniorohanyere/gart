#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <ecraft.h>

/**
 * __c_add_cstory - cast_add_cstory => adds a new cast to a pointer to a
 *		    chat-story/cstory
 *
 * @cstory: pointer to the head of the chat-story
 * @cast: the cast to add to @cstory
 *
 * Return: return nothing
*/

void __c_add_cstory(ecraft_t *cstory, cast_t *cast)
{
	int i = 0, ec_size, size = 4;

	if (cstory->__cast == NULL)
	{
		ec_size = size * (2 * i + 3);

		cstory->__cast = calloc(sizeof(cast_t *), ec_size);
		if (cstory->__cast == NULL)
			return;
	}

	for (i = 0; cstory->__cast[i] != NULL; i++)
		;

	ec_size = size * (2 * i + 3);

	cstory->__cast = realloc(cstory->__cast, sizeof(cast_t *) * ec_size);
	if (cstory->__cast == NULL)
		return;

	cstory->__cast[i] = cast;
}

/**
 * __m_add_cstory - meta_add_cstory => generates and update meta
 *		    information for a craft
 *
 * @meta: pointer to the head metadata
 * @cast: the cast of a craft
 * @emoji: state of the cast at the moment
 * @message: string action of @cast
 * @nmemb: number of @cast member to reference
 *
 * Description: Original Formula/Algorithm: (i + size + (i - 1)) * size
 *		By: Junior Ohanyere <junohanyere@gmail.com>
 *
 *		History: (i + size + (i - 1)) * size)
 *		(i * size * 2) + (size * size) - size
 *		size * (2 * i + 3)	simplified
 *
 *		Where size = 4 bytes represented by 4 int
 *
 * Return: return a pointer to the generated meta information
*/

meta_t **__m_add_cstory(meta_t **meta, cast_t **cast, char **emoji,
	char *message, int nmemb)
{
	int i = 0, j, meta_size, size = 4;

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

	/* update meta information */
	meta[i] = calloc(sizeof(meta_t), 1);
	if (meta[i] == NULL)
	{
		free(meta);
		return (NULL);
	}
	meta[i]->nmemb = nmemb;
	meta[i]->message = strdup(message);
	/* split emoji variable */
	meta[i]->emoji = malloc(sizeof(char **) * nmemb * 1024);
	if (meta[i]->emoji == NULL)
		return (NULL);

	for (j = 0; j < nmemb; j++)
	{
		meta[i]->emoji[j] = __tokenise(emoji[j], " \t\r\n:", 4);
	}
	meta[i]->emoji[j] = NULL;

	meta[i]->cast = cast;

	return (meta);
}

/**
 * __m_del_cstory - meta_del_cstory => deletes/pops out all meta
 *		    information stored in __ecraft for a craft
 *
 * @meta: double pointer to all meta information for a craft
 *
 * Return: return nothing
*/

void __m_del_cstory(meta_t **meta)
{
	int i = 0, j;

	if (meta == NULL)
		return;

	while (meta[i] != NULL)
	{
		free(meta[i]->message);

		for (j = 0; j < meta[i]->nmemb; j++)
			free(meta[i]->emoji[j]);

		free(meta[i]->emoji);

		free(meta[i]);

		i++;
	}

	free(meta);
}

/**
 * __c_del_cstory - cast_del_cstory => deletes all casts associated with a
 *		    given craft
 *
 * @cast: head pointer to the cast to delete
 *
 * Return: return nothing
*/

void __c_del_cstory(cast_t **cast)
{
	int i;

	if (cast == NULL)
		return;

	for (i = 0; cast[i] != NULL; i++)
	{
		free(cast[i]->__dname);
		free(cast[i]->__fname);
		free(cast[i]->__lname);
		free(cast[i]->__altnames);

		free(cast[i]);
	}

	free(cast);
}

/**
 * __free_cstory - frees all memory associated with a given chat-story object
 *
 * @cstory: pointer to the given chat-story object
 *
 * Return: return nothing
*/

void __free_cstory(ecraft_t *cstory)
{
	if (cstory == NULL)
		return;

	if (strcmp(cstory->__type, "ec_cstory") == 0)
	{
		free(cstory->__title);
		free(cstory->__subtitle);
		free(cstory->__description);
		free(cstory->__type);
		free(cstory);
	}
}
