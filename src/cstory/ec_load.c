#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

/**
 * loadcraft - loads a content onto a screen buffer
 *
 * @elem: double pointer to element(s) responsible for the echo
 * @emoji: double pointer to emoji(s) to echo along
 * @string: the content to echo
 * @nmemb: number of elements to reference
 *
 * Return: return the integral location of the echo within __ec->ecraft
*/

int64_t loadcraft(elem_t **elem, char **emoji, char *string, int64_t nmemb)
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
		/* set last parameter to -1 for no ref */
		i = __ec_load(elem, emoji_dup, str, nmemb, -1);
	}
	else
		i = __ec_load(elem, emoji_dup, string, nmemb, -1);

	__ec_read(1);

	for (j = 0; j < nmemb; j++)
		free(emoji_dup[j]);
	free(emoji_dup);

	return (i);
}

/**
 * pullcraft - loads a content to the display/interface, while referencing a
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

int64_t pullcraft(elem_t **elem, char **emoji, char *string, int64_t nmemb,
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
		i = __ec_load(elem, emoji_dup, str, nmemb, ref);
	}
	else
		i = __ec_load(elem, emoji_dup, string, nmemb, ref);

	/* __scrollup(); */

	return (i);
}

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

int64_t __ec_load(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref)
{
	int64_t i, j = (*__ec)->index, size;
	int64_t base_size = 4;	/* 4 bytes */

	i = __ec[j]->ec_size;
	size = base_size * (2 * i + 3);

	if (size == 0)
	{
		/* initialise the ecraft screen placeholder */
		__ec[j]->ecraft = calloc(sizeof(ecraft_t *), size);
		if (__ec[j]->ecraft == NULL)
			return (-1);	/* TODO set up error status */
	}
	else
	{
		__ec[j]->ecraft = realloc(__ec[j]->ecraft,
			sizeof(ecraft_t *) * size);
		if (__ec[j]->ecraft == NULL)
		{
			free(__ec[j]->ecraft);	/* TODO handle error status */
			return (-1);
		}
	}

	/* update screen placeholder by adding a new line buffer */
	i = __ec_load_1(__ec[j]->ecraft, elem, emoji, string, nmemb, ref);

	if (i == -1)
	{
		free(__ec[j]->ecraft);

		return (-1);
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

int64_t __ec_load_1(ecraft_t **ecraft, elem_t **elem, char **emoji,
	char *string, int64_t nmemb, int64_t __attribute__((unused))ref)
{
	int length;
	int64_t i, j = (*__ec)->index, size, r;

	r = __ec[j]->ref;

	if (elem != NULL)
	{
		for (i = 0; i < nmemb; i++)
		{
			size = __ec[j]->ec_size;

			ecraft[size] = calloc(sizeof(ecraft_t), 1);
			if (elem[i] == NULL)
			{
				/* unknown element */
				ecraft[size]->string = strdup("<Unknown>");
			}
			else
				ecraft[size]->string = strdup(
					elem[i]->__dname);
			length = strlen(ecraft[size]->string);
			ecraft[size]->string = realloc(ecraft[size]->string,
				sizeof(char) * length + 2);
			strcat(ecraft[size]->string, ":");

			ecraft[size]->unicode = __ec_split(emoji[i],
				" \t\r\n:", 4);
			ecraft[size]->ref = r;
			ecraft[size]->attrs = EC_BOLD | EC_UNDERLINE;
			ecraft[size]->tts = EC_NONE;

			__ec[j]->ec_size++;
		}
	}
	/* TODO handle @ref here */

	__ec_load_2(ecraft, string, ref);

	ecraft[++__ec[j]->ec_size] = NULL;
	__ec[j]->ref++;

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
	int64_t i = (*__ec)->index, size;

	size = __ec[i]->ec_size;

	/* @string always have a value, can't be NULL */
	if (strcmp(string, "") != 0)
	{
		ecraft[size] = calloc(sizeof(ecraft_t), 1);
		ecraft[size]->string = strdup(string);
		ecraft[size]->attrs = EC_NORMAL;
		ecraft[size]->tts = EC_INIT;
		ecraft[size]->ref = ref;

		__ec[i]->ec_size++;
	}

	size = __ec[i]->ec_size;
	ecraft[size] = calloc(sizeof(ecraft_t), 1);
	ecraft[size]->string = strdup("");
	ecraft[size]->attrs = EC_NORMAL;
	ecraft[size]->ref = -1;
}
