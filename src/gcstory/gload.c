#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gart.h>

/**
 * gload - load the content onto a screen buffer
 *
 * @id: label id
 * @emoji: pointer to emoji to display
 * @string: content to load/display
 *
 * Return: return the integral location of the content within the gbuffer
*/

int64_t gload(int64_t id, const char *str, int ts)
{
	int64_t i, index = (*__art)->index, size;
	glbl_t **label = (*__art)->lbl;

	i = __art[index]->vertice;
	size = i + 2;

	if (i == 0)
	{
		/* initialise the screen buffer */
		__art[index]->scr = calloc(sizeof(gscr_t *), size);
		if (__art[index]->scr == NULL)
			return (-1);	/* TODO set up error status */
	}
	else
	{
		__art[index]->scr = realloc(__art[index]->scr,
			sizeof(gscr_t *) * size);
		if (__art[index]->scr == NULL)
		{
			free(__art[index]->scr);
			return (-1);
		}
	}

	/* update screen buffer */
	"this is how I want my text to look like [:c-f], this feels good!"
	"and [u:f-b-a-k] this too [t:s-f]"
	__gread(1);

	return (i);
}

/**
 * __gload - updates __art->scr
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

int64_t __gload(glbl_t *lbl, char *emoji, char *string)
{
	int64_t index = (*__art)->index, size, base_size = 4;	/* 4 bytes */
	int64_t i = __art[index]->vertice;

	size = base_size * (2 * i + 3);

	if (i == 0)
	{
		/* initialise the screen buffer */
		__art[index]->scr = calloc(sizeof(gscr_t *), size);
		if (__art[index]->scr == NULL)
			return (-1);	/* TODO set up error status */
	}
	else
	{
		__art[index]->scr = realloc(__art[index]->scr,
			sizeof(gscr_t *) * size);
		if (__art[index]->scr == NULL)
		{
			free(__art[index]->scr);

			return (-1);
		}
	}

	/* update screen buffer by adding a new line buffer */
	i = __gload_1(__art[index]->scr, lbl, emoji, string);
	if (i == -1)
		free(__art[index]->scr);

	return (i);
}

/**
 * __gload_1 - extension of __gload
 *
 * @scr: double pointer to screen buffer
 * @elem: pointer to element to load into the screen buffer
 * @emoji: pointer to emoji to load into the screen buffer
 * @string: string to load into the screen buffer
 *
 * Return: return a reference number on success
 * 	   return -1 on failure
*/

int64_t __gload_1(gscr_t **scr, glbl_t *lbl, char *emoji, char *string)
{
	int i;
	int64_t index = (*__art)->index, size, r = __art[index]->ref;

	size = __art[index]->vertice;

	scr[size] = calloc(sizeof(gscr_t), 1);
	if (lbl == NULL)
	{
		/* unknown element */
		scr[size]->string = strdup("<Unknown>");
	}
	else
		scr[size]->string = strdup(lbl->__dname);

	i = strlen(scr[size]->string);

	scr[size]->string = realloc(scr[size]->string, sizeof(char) * i + 2);

	strcat(scr[size]->string, ":");

	scr[size]->unicode = __gsplit(emoji, " \t\r\n:", 4);
	scr[size]->ref = r;
	scr[size]->attrs = GBOLD | GUNDERLINE;
	scr[size]->tts = GNONE;

	__art[index]->vertice++;

	__gload_2(scr, string, r);

	scr[++__art[index]->vertice] = NULL;
	__art[index]->ref++;

	return (r);
}

/**
 * __gload_2 - extension of __gload_1
 *
 * @scr: double pointer to screen buffer
 * @string: string to load into the screen buffer
 * @ref: reference number
 *
 * Return: return nothing
*/

void __gload_2(gscr_t **scr, char *string, int64_t ref)
{
	int64_t index = (*__art)->index, size;

	size = __art[index]->vertice;

	if (strcmp(string, "") != 0)
	{
		scr[size] = calloc(sizeof(gscr_t), 1);
		scr[size]->string = strdup(string);
		scr[size]->attrs = GNORMAL;
		scr[size]->tts = GINIT;
		scr[size]->ref = ref;

		__art[index]->vertice++;
	}

	size = __art[index]->vertice;
	scr[size] = calloc(sizeof(gscr_t), 1);
	scr[size]->string = strdup("");
	scr[size]->attrs = GNORMAL;
	scr[size]->ref = -1;
}
