#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

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

/**
 * ec_update - updates the interface screen
 *
 * Return: return nothing
*/

void ec_update(void)
{
	switch (__ec->interf)
	{
		case EC_NONE:
			break;	/* do nothing */

		case EC_CLI:
			#ifdef _CRAFT

			#if _CRAFT == 1
			__cs_update_cli(__ec->ecraft[__ec->bottom]);
			#endif	/* _CRAFT == 1 */

			#endif	/* _CRAFT */

			break;

		case EC_GUI:
			/* TODO */

			break;

		default:
			dprintf(STDERR_FILENO,
				"invalid interface: no such interface");
			abort();

			return;
	}
}

/**
 * __cs_update_cli - updates the command line interface screen for a chat story
 *
 * @ecraft: pointer to a meta data
 *
 * Return: return nothing
*/

void __cs_update_cli(ecraft_t *ecraft)
{
	int y;
	int64_t i;

	y = getcury(stdscr);
	if (y == getmaxy(stdscr))
	{
		scrl(1);
		refresh();
	}
	/* display names should be printed in bold */
	if (ecraft->elem != NULL)
	{
		for (i = 0; i < ecraft->nmemb; i++)
		{
			/* ecraft->ref check should be here */
			attron(A_BOLD);
			if (ecraft->elem[i] == NULL)
			{
				/* unknown element */
				__ec_printf("string", "<Unknown>");
			}
			else
			{
				__ec_printf("string",
					ecraft->elem[i]->__dname);
			}
			__ec_printf("string", ": ");
			attroff(A_BOLD);
			if (ecraft->emoji != NULL && ecraft->emoji[i] != NULL)
				__cs_emoji(ecraft->emoji[i]);
			__ec_printf("string", "\n");
			/* next element */
		}
	}	/* if element is NULL, just print the string message */
	__ec_printf("string", ecraft->string);
	if (strcmp(ecraft->string, "\r") != 0)
		__ec_printf("string", "\n");
	__ec_printf("string", "\n");
}
