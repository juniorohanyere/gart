#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

/**
 * ec_load - loads a content onto a screen buffer
 *
 * @elem: double pointer to element(s) responsible for the echo
 * @emoji: double pointer to emoji(s) to echo along
 * @string: the content to echo
 *
 * Return: return the integral location of the echo within __ec->ecraft
*/

int64_t ec_load(elem_t *elem, char *emoji, char *string)
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

	i = __ec_load(elem, emoji_dup, string_dup);

	__ec_read(1);

	free(string_dup);
	free(emoji_dup);

	return (i);
}

/**
 * ec_tag - loads a content to the display/interface, while referencing a
 *	      previous content
 *
 * @elem: double pointer to element(s) responsible for the echo
 * @emoji: double pointer to emoji(s) to echo along
 * @string: the content to echo
 * @nmemb: number of elements to reference
 * @ref: reference number of content to reference
 *
 * Return: return the integral location of the echo within __ec->ecraft
*/


/**
 * __ec_load - updates __ec->ecraft placeholder for a chat story
 *
 * @elem: pointer to an array of elements for the craft
 * @emoji: state of the element at the moment
 * @string: string to send to display
 * @nmemb: number of @elem member to reference
 * @ref: reference number of line buffer to re-reference/reload
 *
 * Description: Original Formula/Algorithm: (i + size + (i - 1)) * size
 *		By: Junior Ohanyere <juniorohanyere@gmail.com>
 *
 *		History: (i + size + (i - 1)) * size) modified to:
 *			 (i * size * 2) + (size * size) - size modified to:
 *			 size * (2 * i + 3) simplified
 *
 *		Where size = base size (4 bytes represented by 4 int)
 *
 * Return: return a pointer to the index location of the echo within
 *	   __ec->ecraft list
 *	   return -1 on failure
*/

int64_t __ec_load(elem_t *elem, char *emoji, char *string)
{
	int64_t i = __ec->ec_size, size, base_size = 4;	/* 4 bytes */

	size = base_size * (2 * i + 3);

	if (size == 0)
	{
		/* initialise the ecraft screen placeholder */
		__ec->ecraft = calloc(sizeof(ecraft_t *), size);
		if (__ec->ecraft == NULL)
			return (-1);	/* TODO set up error status */
	}
	else
	{
		__ec->ecraft = realloc(__ec->ecraft, sizeof(ecraft_t *) * size);
		if (__ec->ecraft == NULL)
		{
			free(__ec->ecraft);	/* TODO handle error status */
			return (-1);
		}
	}

	/* update screen placeholder by adding a new line buffer */
	i = __ec_load_1(__ec->ecraft, elem, emoji, string);

	if (i == -1)
	{
		free(__ec->ecraft);

		return (i);
	}

	return (i);
}

/**
 * __ec_load_1 - extension of __ec_load
 *
 * @ecraft: pointer to a list of ecraft
 * @elem: element to load into @ecraft
 * @emoji: double pointer to emoji(s) to load into @ecraft
 * @string: string to load into @ecraft
 * @nmemb: number of elements to reference
 * @ref: reference number of line buffer to re-referece (is that even a word?)
 *
 * Return: return a reference number on success
 *	   return -1 on failure
*/

int64_t __ec_load_1(ecraft_t **ecraft, elem_t *elem, char *emoji, char *string)
{
	int i;
	int64_t size, r = __ec->ref;

	size = __ec->ec_size;

	ecraft[size] = calloc(sizeof(ecraft_t), 1);
	if (elem == NULL)
	{
		/* unknown element */
		ecraft[size]->string = strdup("<Unknown>");
	}
	else
		ecraft[size]->string = strdup(
			elem->__dname);
	i = strlen(ecraft[size]->string);
	ecraft[size]->string = realloc(ecraft[size]->string,
		sizeof(char) * i + 2);
	strcat(ecraft[size]->string, ":");

	ecraft[size]->unicode = __ec_split(emoji, " \t\r\n:", 4);
	ecraft[size]->ref = r;
	ecraft[size]->attrs = EC_BOLD | EC_UNDERLINE;
	ecraft[size]->tts = EC_NONE;

	__ec->ec_size++;

	__ec_load_2(ecraft, string, r);

	ecraft[++__ec->ec_size] = NULL;
	__ec->ref++;

	return (r);
}

/**
 * __ec_load_2 - extension of __ec_load_1
 *
 * @ecraft: pointer to a list of ecraft
 * @string: string to load into @ecraft
 * @ref: reference number
 *
 * Return: return nothing
*/

void __ec_load_2(ecraft_t **ecraft, char *string, int64_t ref)
{
	int64_t size;

	size = __ec->ec_size;

	if (strcmp(string, "") != 0)
	{
		ecraft[size] = calloc(sizeof(ecraft_t), 1);
		ecraft[size]->string = strdup(string);
		ecraft[size]->attrs = EC_NORMAL;
		ecraft[size]->tts = EC_INIT;
		ecraft[size]->ref = ref;

		__ec->ec_size++;
	}

	size = __ec->ec_size;
	ecraft[size] = calloc(sizeof(ecraft_t), 1);
	ecraft[size]->string = strdup("");
	ecraft[size]->attrs = EC_NORMAL;
	ecraft[size]->ref = -1;
}
