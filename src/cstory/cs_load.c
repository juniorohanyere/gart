#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

/**
 * ec_load - loads a content to a given interface pointed to by __ec->interf
 *
 * @elem: double pointer to element(s) responsible for the echo
 * @emoji: double pointer to emoji(s) to echo along
 * @string: the content to echo
 * @nmemb: number of elements to reference
 *
 * Return: return the integral location of the echo within __ec->ecraft
*/

int64_t ec_load(elem_t **elem, char **emoji, char *string, int64_t nmemb)
{
	int64_t i, j;
	char *str = "";
	char **emoji_dup;

	emoji_dup = malloc(sizeof(char *) * nmemb);

	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji_dup[i] = strdup(str);
		else
			emoji_dup[i] = strdup(emoji[i]);
	}
	if (string == NULL)
	{
		str = "\r";	/* sentinel value to track NULL string */
		/* set last parameter to -1 for no ref */
		i = __cs_load(elem, emoji_dup, str, nmemb, -1);
	}
	else
		i = __cs_load(elem, emoji_dup, string, nmemb, -1);

	ec_update();

	__ec_interrupt(__ec->ecraft[i]->string);

	for (j = 0; j < nmemb; j++)
		free(emoji_dup[j]);
	free(emoji_dup);

	return (i);
}

/**
 * ec_pull - loads a content to the display/interface, while referencing a
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

int64_t ec_pull(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref)
{
	int64_t i;
	char *str = "";	/* so as not to modify the original string(s) passed */
	char **emoji_dup;

	emoji_dup = malloc(sizeof(char *) * nmemb);

	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji_dup[i] = strdup(str);
		else
			emoji_dup[i] = strdup(emoji[i]);
	}

	if (string == NULL)
	{
		str = "\r";	/* sentinel value to track NULL string */
		/* set last parameter to value of @ref */
		i = __cs_load(elem, emoji_dup, str, nmemb, ref);
	}
	else
		i = __cs_load(elem, emoji_dup, string, nmemb, ref);

	clear();
	ec_update();

	__ec_interrupt(__ec->ecraft[i]->string);

	return (i);
}

/**
 * __cs_load - updates __ec->ecraft placeholder for a chat story
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

int64_t __cs_load(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref)
{
	int64_t i = 0, j, ec_size, base_size = 4;	/* 4 bytes */

	if (__ec->ecraft == NULL)
	{
		/* initialise the ecraft screen buffer */
		ec_size = base_size * (2 * i + 3);
		__ec->ecraft = calloc(sizeof(ecraft_t *), ec_size);
		if (__ec->ecraft == NULL)
			return (-1);	/* TODO set up error status */
	}
	else
	{
		/* get the size/number of the lines */
		for (i = 0; __ec->ecraft[i] != NULL; i++)
			;
		ec_size = base_size * (2 * i + 3);	/* cool formula */
		__ec->ecraft = realloc(__ec->ecraft,
			sizeof(ecraft_t *) * ec_size);
		if (__ec->ecraft == NULL)
		{
			free(__ec->ecraft);	/* TODO handle error status */
			return (-1);
		}
	}

	/* update screen buffer */
	__ec->ecraft[i] = calloc(sizeof(ecraft_t), 1);
	if (__ec->ecraft[i] == NULL)
		return (-1);

	j = __cs_load_index(__ec->ecraft[i], elem, emoji, string, nmemb, ref);
	if (j == -1)
	{
		free(__ec->ecraft);

		return (-1);
	}

	return (i);
}

/**
 * __cs_load_index - loads the index of __ec->ecraft, (see __cs_load)
 *
 * @ecraft: an index of __ec->ecraft
 * @elem: element to load into @ecraft
 * @emoji: double pointer to emoji(s) to load into @ecraft
 * @string: string to load into @ecraft
 * @nmemb: number of elements to reference
 * @ref: reference number of line buffer to re-referece (is that even a word?)
 *
 * Return: return 0 on success
 *	   return -1 on failure
*/

int64_t __cs_load_index(ecraft_t *ecraft, elem_t **elem, char **emoji,
	char *string, int64_t nmemb, int64_t ref)
{
	int64_t i, base_size = 4;

	ecraft->elem = elem;

	/*
	 * this formula really works like magic for valgrind invalid read
	 * and/or of size
	*/
	ecraft->emoji = calloc(sizeof(char **), base_size * (2 * nmemb + 3));
	if (ecraft->emoji == NULL)
	{
		free(ecraft);

		return (-1);
	}
	for (i = 0; i < nmemb; i++)
	{
		ecraft->emoji[i] = __ec_split(emoji[i], " \t\r\n:", 4);
	}
	ecraft->emoji[i] = NULL;	/* NULL termination */

	/*
	 * TODO need to split up @string setting new line as the delimiter, and
	 * assign the results to a new index of __ec->ecraft, so that ecraft
	 * can support line buffering, and also for performance purpose
	*/
	ecraft->string = strdup(string);
	if (ecraft->string == NULL)
	{
		free(ecraft);

		return (-1);
	}
	ecraft->nmemb = nmemb;
	ecraft->ref = ref;

	__ec->bottom++;

	return (0);
}
