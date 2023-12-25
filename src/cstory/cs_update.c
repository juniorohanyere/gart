#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ecraft.h>

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
