#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gart.h>

/**
 * gload - load the content onto a screen buffer
 *
 * @elem: pointer to an element
 * @emoji: pointer to emoji to display
 * @string: content to load/display
 *
 * Return: return the integral location of the content within the gbuffer
*/

int64_t gload(elem_t *elem, char *emoji, char *string)
{
	int64_t i;
	char *str = "", *string_dup, *emoji_dup;

	if (emoji == NULL)
		emoji_dup = strdup(str);
	else
		emoji_dup = strdup(emoji);

	if (string == NULL)
		string_dup = strdup(str);
	else
		string_dup = strdup(string);

	i = __gload(elem, emoji_dup, string_dup);

	__gread(1);

	free(string_dup);
	free(emoji_dup);

	return (i);
}

/**
 * __gload - updates __art->gbuffer
 *
 * @elem: pointer to an array of elements for the art
 * @emoji: state/mood of @elem at the moment
 * @string: string to load
 *
 * Description: Original Formula/Algorithm: (i + size + (i - 1)) * size
 *		By: Junior Ohanyere <junohanyere@gmail.com>
 *
 *		History: (i + size + (i - 1)) * size) modified to:
 *			 (i * size * 2) + (size * size) - size modified to:
 *			 size * (2 * i + 3) simplified
 *
 *		where size = base size (4 bytes represented by 4 int)
 *
 * Return: return a pointer to the index location of the loaded content
 *	   return -1 on failure
*/

int64_t __gload(elem_t *elem, char *emoji, char *string)
{
	int64_t i = __art->vertice, size, base_size = 4;	/* 4 bytes */

	size = base_size * (2 * i + 3);

	if (size == 0)
	{
		/* initialise the screen buffer */
		__art->gbuffer = calloc(sizeof(gbuffer_t *), size);
		if (__art->gbuffer == NULL)
			return (-1);	/* TODO set up error status */
	}
	else
	{
		__art->gbuffer = realloc(__art->gbuffer,
			sizeof(gbuffer_t *) * size);
		if (__art->gbuffer == NULL)
		{
			free(__art->gbuffer);

			return (-1);
		}
	}

	/* update screen buffer by adding a new line buffer */
	i = __gload_1(__art->gbuffer, elem, emoji, string);
	if (i == -1)
		free(__art->gbuffer);

	return (i);
}

/**
 * __gload_1 - extension of __gload
 *
 * @gbuffer: double pointer to screen buffer
 * @elem: pointer to element to load into the screen buffer
 * @emoji: pointer to emoji to load into the screen buffer
 * @string: string to load into the screen buffer
 *
 * Return: return a reference number on success
 * 	   return -1 on failure
*/

int64_t __gload_1(gbuffer_t **gbuffer, elem_t *elem, char *emoji, char *string)
{
	int i;
	int64_t size, r = __art->ref;

	size = __art->vertice;

	gbuffer[size] = calloc(sizeof(gbuffer_t), 1);
	if (elem == NULL)
	{
		/* unknown element */
		gbuffer[size]->string = strdup("<Unknown>");
	}
	else
		gbuffer[size]->string = strdup(elem->__dname);

	i = strlen(gbuffer[size]->string);

	gbuffer[size]->string = realloc(gbuffer[size]->string,
		sizeof(char) * i + 2);

	strcat(gbuffer[size]->string, ":");

	gbuffer[size]->unicode = __gsplit(emoji, " \t\r\n:", 4);
	gbuffer[size]->ref = r;
	gbuffer[size]->attrs = GBOLD | GUNDERLINE;
	gbuffer[size]->tts = GNONE;

	__art->vertice++;

	__gload_2(gbuffer, string, r);

	gbuffer[++__art->vertice] = NULL;
	__art->ref++;

	return (r);
}

/**
 * __gload_2 - extension of __gload_1
 *
 * @gbuffer: double pointer to screen buffer
 * @string: string to load into the screen buffer
 * @ref: reference number
 *
 * Return: return nothing
*/

void __gload_2(gbuffer_t **gbuffer, char *string, int64_t ref)
{
	int64_t size;

	size = __art->vertice;

	if (strcmp(string, "") != 0)
	{
		gbuffer[size] = calloc(sizeof(gbuffer_t), 1);
		gbuffer[size]->string = strdup(string);
		gbuffer[size]->attrs = GNORMAL;
		gbuffer[size]->tts = GINIT;
		gbuffer[size]->ref = ref;

		__art->vertice++;
	}

	size = __art->vertice;
	gbuffer[size] = calloc(sizeof(gbuffer_t), 1);
	gbuffer[size]->string = strdup("");
	gbuffer[size]->attrs = GNORMAL;
	gbuffer[size]->ref = -1;
}
