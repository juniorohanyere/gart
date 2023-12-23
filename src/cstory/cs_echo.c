#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

#ifdef _CRAFT

#if _CRAFT == 1

int64_t ec_echo(elem_t **elem, char **emoji, char *string, int64_t nmemb)
{
	int64_t i;
	char *str = "";
	char **emoji_dup;

	emoji_dup = malloc(sizeof(char *) * nmemb);

	if (string == NULL)
		string = "\r";	/* sentinel value to track NULL string */

	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji_dup[i] = strdup(str);
		else
			emoji_dup[i] = strdup(emoji[i]);
	}

	/* set last parameter to -1 for no ref */
	i = __cs_update(elem, emoji_dup, string, nmemb, -1);

	return (i);
}

int64_t ec_recho(elem_t **elem, char **emoji, char *string, int64_t nmemb,
	int64_t ref)
{
	int64_t i;
	char *str = "";
	char **emoji_dup;

	emoji_dup = malloc(sizeof(char *) * nmemb);

	if (string == NULL)
		string = "\r";	/* sentinel value to track NULL string */

	for (i = 0; i < nmemb; i++)
	{
		if (emoji[i] == NULL)
			emoji_dup[i] = strdup(str);
		else
			emoji_dup[i] = strdup(emoji[i]);
	}

	/* set last parameter to value of @ref */
	i = __cs_update(elem, emoji_dup, string, nmemb, ref);
	__cs_display(__ec->ecraft[i]);

	return (i);
}
#endif	/* _CRAFT == 1 */

#endif	/* _CRAFT */

/**
 * __cs_update - updates __ec->ecraft placeholder for a chat story
 *
 * @elem: pointer to an array of elements for the craft
 * @emoji: state of the element at the moment
 * @string: string to send to display
 * @nmemb: number of @elem member to reference
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

int64_t __cs_update(elem_t **elem, char **emoji, char *string, int64_t nmemb,
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
	/* get the size/number of the lines */
	for (i = 0; __ec->ecraft[i] != NULL; i++)
		;
	ec_size = base_size * (2 * i + 3);	/* cool formula */
	__ec->ecraft = realloc(__ec->ecraft, sizeof(ecraft_t *) * ec_size);
	if (__ec->ecraft == NULL)
	{
		free(__ec->ecraft);	/* TODO handle error status */

		return (-1);
	}

	/* update screen buffer */
	__ec->ecraft[i] = calloc(sizeof(ecraft_t), 1);
	if (__ec->ecraft[i] == NULL)
	{
		free(__ec->ecraft);

		return (-1);
	}

	__ec->ecraft[i]->elem = elem;

	for (j = 0; j < nmemb; j++)
	{
		__ec->ecraft[i]->emoji[j] = __ec_split(emoji[j], " \t\r\n:", 4
		);
	}
	__ec->ecraft[i]->emoji[j] = NULL;	/* NULL termination */

	__ec->ecraft[i]->string = strdup(string);
	if (__ec->ecraft[i]->string == NULL)
	{
		free(__ec->ecraft[i]);

		return (-1);
	}

	__ec->ecraft[i]->nmemb = nmemb;
	__ec->ecraft[i]->ref = ref;

	return (i);
}

void __cs_display(ecraft_t *ecraft)
{
	switch (__ec->interf)
	{
		case EC_NONE:
			break;	/* do nothing */
		case EC_CLI:
			__cs_display_cli(ecraft);

			break;

		case EC_GUI:
			/* __ec_display_gui(ecraft); TODO */

			break;

		default:
			dprintf(STDERR_FILENO,
				"invalid interface: coundn't locate interface"
			);
			abort();

			return;
	}
}

void __cs_display_cli(ecraft_t *ecraft)
{
	int64_t i;

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

	__ec_interrupt(ecraft->string);
}
